import argparse
import copy
import faulthandler
import json
import os
import sys
import time

torch = None


def stage(message):
    print(f"[benchmark] {message}", flush=True)


def parse_args():
    parser = argparse.ArgumentParser(
        description="PyTorch CUDA Graph benchmark for the GVirtuS frontend."
    )
    parser.add_argument("--batch-size", type=int, default=640)
    parser.add_argument("--input-dim", type=int, default=4096)
    parser.add_argument("--hidden-dim", type=int, default=2048)
    parser.add_argument("--output-dim", type=int, default=1024)
    parser.add_argument("--warmup-iters", type=int, default=3)
    parser.add_argument("--benchmark-iters", type=int, default=20)
    parser.add_argument("--learning-rate", type=float, default=0.1)
    parser.add_argument("--dtype", choices=("float32", "float16"), default="float32")
    parser.add_argument("--seed", type=int, default=1234)
    parser.add_argument("--atol", type=float, default=1e-5)
    parser.add_argument("--rtol", type=float, default=1e-4)
    parser.add_argument("--fail-on-mismatch", action="store_true")
    parser.add_argument("--output-json", type=str, default="")
    parser.add_argument("--output-csv", type=str, default="")
    parser.add_argument("--num-runs", type=int, default=1)
    return parser.parse_args()


def make_model(input_dim, hidden_dim, output_dim, dtype):
    model = torch.nn.Sequential(
        torch.nn.Linear(input_dim, hidden_dim),
        torch.nn.ReLU(),
        torch.nn.Linear(hidden_dim, output_dim),
    ).cuda()
    return model.to(dtype=dtype)


def make_batches(num_batches, batch_size, input_dim, output_dim, dtype):
    inputs = [
        torch.randn(batch_size, input_dim, device="cuda", dtype=dtype)
        for _ in range(num_batches)
    ]
    targets = [
        torch.randn(batch_size, output_dim, device="cuda", dtype=dtype)
        for _ in range(num_batches)
    ]
    return inputs, targets


def run_eager(model, loss_fn, optimizer, inputs, targets):
    iter_times_ms = []
    losses = []
    for data, target in zip(inputs, targets):
        torch.cuda.synchronize()
        t0 = time.perf_counter()
        optimizer.zero_grad(set_to_none=True)
        prediction = model(data)
        loss = loss_fn(prediction, target)
        loss.backward()
        optimizer.step()
        torch.cuda.synchronize()
        iter_times_ms.append((time.perf_counter() - t0) * 1000.0)
        # Read the loss after synchronize so GVirtuS has flushed the forward
        # pass to the backend before we issue the D2H transfer.  The loss
        # tensor itself is not freed by backward() — only intermediate
        # activations used for gradient computation are released.
        losses.append(loss.item())
    elapsed_ms = sum(iter_times_ms)
    return elapsed_ms, losses, iter_times_ms


def warmup_model(model, loss_fn, optimizer, inputs, targets):
    # PyTorch's wait_stream() path records CUDA events under the hood.
    # GVirtuS currently trips on that event-based synchronization sequence,
    # so keep warmup on the current stream for this frontend validation test.
    for data, target in zip(inputs, targets):
        optimizer.zero_grad(set_to_none=True)
        loss = loss_fn(model(data), target)
        loss.backward()
        optimizer.step()
    torch.cuda.synchronize()


def run_graphed(model, loss_fn, optimizer, warmup_inputs, warmup_targets, bench_inputs, bench_targets):
    static_input = torch.empty_like(bench_inputs[0])
    static_target = torch.empty_like(bench_targets[0])
    static_input.copy_(warmup_inputs[-1])
    static_target.copy_(warmup_targets[-1])

    warmup_model(model, loss_fn, optimizer, warmup_inputs, warmup_targets)

    # Capture executes the step once, so snapshot and restore state to keep the
    # graphed benchmark aligned with the eager benchmark iteration count.
    captured_model_state = copy.deepcopy(model.state_dict())
    captured_optimizer_state = copy.deepcopy(optimizer.state_dict())

    # Pre-allocate a scalar tensor OUTSIDE the graph context so it lives in
    # PyTorch's normal CUDA allocator (not the graph memory pool).  The copy
    # captured inside the graph writes the loss value here on every replay,
    # giving a reliably-readable result.
    static_loss_record = torch.zeros([], device="cuda")

    graph = torch.cuda.CUDAGraph()
    optimizer.zero_grad(set_to_none=True)
    with torch.cuda.graph(graph):
        static_prediction = model(static_input)
        static_loss = loss_fn(static_prediction, static_target)
        static_loss_record.copy_(static_loss)  # replayed each iteration
        static_loss.backward()
        optimizer.step()
    torch.cuda.synchronize()

    model.load_state_dict(captured_model_state)
    optimizer.load_state_dict(captured_optimizer_state)
    optimizer.zero_grad(set_to_none=True)

    iter_times_ms = []
    losses = []
    for data, target in zip(bench_inputs, bench_targets):
        static_input.copy_(data)
        static_target.copy_(target)
        torch.cuda.synchronize()
        t0 = time.perf_counter()
        graph.replay()
        torch.cuda.synchronize()
        iter_times_ms.append((time.perf_counter() - t0) * 1000.0)
        losses.append(static_loss_record.item())
    elapsed_ms = sum(iter_times_ms)

    return elapsed_ms, losses, iter_times_ms


def compare_models(reference_model, candidate_model):
    max_abs_diff = 0.0
    for ref_param, candidate_param in zip(reference_model.parameters(), candidate_model.parameters()):
        max_abs_diff = max(
            max_abs_diff,
            float((ref_param.detach() - candidate_param.detach()).abs().max().cpu()),
        )
    return max_abs_diff


def main():
    global torch
    faulthandler.enable(all_threads=True)
    stage(f"python={sys.version.split()[0]} pid={os.getpid()}")
    stage("importing torch")
    import torch as torch_module
    torch = torch_module
    stage(f"torch imported version={torch.__version__}")

    args = parse_args()
    stage("checking torch.cuda.is_available()")
    if not torch.cuda.is_available():
        raise SystemExit("CUDA is not available from PyTorch. Check the GVirtuS frontend setup.")
    stage("CUDA reported available")

    dtype = torch.float16 if args.dtype == "float16" else torch.float32

    # Open CSV in append mode; write header only if the file is new/empty.
    csv_file = None
    if args.output_csv:
        csv_exists = os.path.exists(args.output_csv) and os.path.getsize(args.output_csv) > 0
        csv_file = open(args.output_csv, "a", newline="", encoding="utf-8")  # noqa: SIM115
        if not csv_exists:
            csv_file.write("run,mode,iter,batch_size,input_dim,hidden_dim,output_dim,dtype,iter_ms\n")

    any_mismatch = False
    try:
        for run_idx in range(args.num_runs):
            if args.num_runs > 1:
                stage(f"=== run {run_idx + 1}/{args.num_runs} ===")

            run_seed = args.seed + run_idx
            torch.manual_seed(run_seed)
            torch.cuda.manual_seed_all(run_seed)
            stage("seeds set")

            total_iters = args.warmup_iters + args.benchmark_iters
            stage("allocating input and target batches")
            inputs, targets = make_batches(
                total_iters,
                args.batch_size,
                args.input_dim,
                args.output_dim,
                dtype,
            )
            warmup_inputs = inputs[: args.warmup_iters]
            warmup_targets = targets[: args.warmup_iters]
            bench_inputs = inputs[args.warmup_iters :]
            bench_targets = targets[args.warmup_iters :]
            stage("batch allocation complete")

            stage("building models and optimizers")
            eager_model = make_model(args.input_dim, args.hidden_dim, args.output_dim, dtype)
            graph_model = copy.deepcopy(eager_model)
            loss_fn_eager = torch.nn.MSELoss()
            loss_fn_graph = torch.nn.MSELoss()
            eager_optimizer = torch.optim.SGD(eager_model.parameters(), lr=args.learning_rate)
            graph_optimizer = torch.optim.SGD(graph_model.parameters(), lr=args.learning_rate)
            stage("models ready")

            stage("running eager warmup")
            _, _, _ = run_eager(
                eager_model,
                loss_fn_eager,
                eager_optimizer,
                warmup_inputs,
                warmup_targets,
            )
            stage("running eager benchmark")
            eager_elapsed_ms, eager_losses, eager_iter_times = run_eager(
                eager_model,
                loss_fn_eager,
                eager_optimizer,
                bench_inputs,
                bench_targets,
            )
            stage("running graphed benchmark")
            graph_elapsed_ms, graph_losses, graph_iter_times = run_graphed(
                graph_model,
                loss_fn_graph,
                graph_optimizer,
                warmup_inputs,
                warmup_targets,
                bench_inputs,
                bench_targets,
            )
            stage("graphed benchmark complete")

            if csv_file:
                for i, (ms, _loss) in enumerate(zip(eager_iter_times, eager_losses)):
                    csv_file.write(
                        f"{run_idx + 1},eager,{i},{args.batch_size},{args.input_dim},"
                        f"{args.hidden_dim},{args.output_dim},{args.dtype},{ms:.4f}\n"
                    )
                for i, (ms, _loss) in enumerate(zip(graph_iter_times, graph_losses)):
                    csv_file.write(
                        f"{run_idx + 1},graphed,{i},{args.batch_size},{args.input_dim},"
                        f"{args.hidden_dim},{args.output_dim},{args.dtype},{ms:.4f}\n"
                    )
                csv_file.flush()

            max_param_abs_diff = compare_models(eager_model, graph_model)
            final_loss_close = torch.isclose(
                torch.tensor(eager_losses[-1]),
                torch.tensor(graph_losses[-1]),
                atol=args.atol,
                rtol=args.rtol,
            ).item()

            summary = {
                "run": run_idx + 1,
                "batch_size": args.batch_size,
                "benchmark_iters": args.benchmark_iters,
                "dtype": args.dtype,
                "eager_ms_total": round(eager_elapsed_ms, 3),
                "graph_ms_total": round(graph_elapsed_ms, 3),
                "eager_ms_per_iter": round(eager_elapsed_ms / args.benchmark_iters, 3),
                "graph_ms_per_iter": round(graph_elapsed_ms / args.benchmark_iters, 3),
                "speedup": round(eager_elapsed_ms / graph_elapsed_ms, 3) if graph_elapsed_ms else None,
                "eager_final_loss": eager_losses[-1],
                "graph_final_loss": graph_losses[-1],
                "final_loss_close": bool(final_loss_close),
                "max_param_abs_diff": max_param_abs_diff,
                "warmup_iters": args.warmup_iters,
            }

            print(f"GVirtuS PyTorch CUDA Graph benchmark - run {run_idx + 1}/{args.num_runs}")
            print(json.dumps(summary, indent=2, sort_keys=True))

            if args.output_json and run_idx == args.num_runs - 1:
                with open(args.output_json, "w", encoding="utf-8") as f:
                    json.dump(summary, f, indent=2, sort_keys=True)
                    f.write("\n")
                stage(f"wrote summary to {args.output_json}")

            if not final_loss_close:
                any_mismatch = True
                if args.fail_on_mismatch:
                    raise SystemExit(
                        "Graph replay completed, but the final eager and graphed losses diverged beyond tolerance."
                    )

            # Free GPU memory before the next run.
            del eager_model, graph_model, eager_optimizer, graph_optimizer
            del inputs, targets
            torch.cuda.empty_cache()
    finally:
        if csv_file:
            csv_file.close()
            stage(f"wrote per-iteration results to {args.output_csv}")

    if any_mismatch and not args.fail_on_mismatch:
        stage("WARNING: one or more runs had eager/graphed loss divergence beyond tolerance")


if __name__ == "__main__":
    main()
