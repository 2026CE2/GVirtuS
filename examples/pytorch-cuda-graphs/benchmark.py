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
    losses = []
    torch.cuda.synchronize()
    start = time.perf_counter()
    for data, target in zip(inputs, targets):
        optimizer.zero_grad(set_to_none=True)
        prediction = model(data)
        loss = loss_fn(prediction, target)
        loss.backward()
        optimizer.step()
        losses.append(float(loss.detach().cpu()))
    torch.cuda.synchronize()
    elapsed_ms = (time.perf_counter() - start) * 1000.0
    return elapsed_ms, losses


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

    graph = torch.cuda.CUDAGraph()
    optimizer.zero_grad(set_to_none=True)
    with torch.cuda.graph(graph):
        static_prediction = model(static_input)
        static_loss = loss_fn(static_prediction, static_target)
        static_loss.backward()
        optimizer.step()
    torch.cuda.synchronize()

    model.load_state_dict(captured_model_state)
    optimizer.load_state_dict(captured_optimizer_state)
    optimizer.zero_grad(set_to_none=True)

    losses = []
    torch.cuda.synchronize()
    start = time.perf_counter()
    for data, target in zip(bench_inputs, bench_targets):
        static_input.copy_(data)
        static_target.copy_(target)
        graph.replay()
        losses.append(float(static_loss.detach().cpu()))
    torch.cuda.synchronize()
    elapsed_ms = (time.perf_counter() - start) * 1000.0

    return elapsed_ms, losses


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

    torch.manual_seed(args.seed)
    if torch.cuda.is_available():
        torch.cuda.manual_seed_all(args.seed)
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
    _, _ = run_eager(
        eager_model,
        loss_fn_eager,
        eager_optimizer,
        warmup_inputs,
        warmup_targets,
    )
    stage("running eager benchmark")
    eager_elapsed_ms, eager_losses = run_eager(
        eager_model,
        loss_fn_eager,
        eager_optimizer,
        bench_inputs,
        bench_targets,
    )
    stage("running graphed benchmark")
    graph_elapsed_ms, graph_losses = run_graphed(
        graph_model,
        loss_fn_graph,
        graph_optimizer,
        warmup_inputs,
        warmup_targets,
        bench_inputs,
        bench_targets,
    )
    stage("graphed benchmark complete")

    max_param_abs_diff = compare_models(eager_model, graph_model)
    final_loss_close = torch.isclose(
        torch.tensor(eager_losses[-1]),
        torch.tensor(graph_losses[-1]),
        atol=args.atol,
        rtol=args.rtol,
    ).item()

    summary = {
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

    print("GVirtuS PyTorch CUDA Graph benchmark")
    print(json.dumps(summary, indent=2, sort_keys=True))

    if args.output_json:
        with open(args.output_json, "w", encoding="utf-8") as f:
            json.dump(summary, f, indent=2, sort_keys=True)
            f.write("\n")
        stage(f"wrote summary to {args.output_json}")

    if not final_loss_close and args.fail_on_mismatch:
        raise SystemExit(
            "Graph replay completed, but the final eager and graphed losses diverged beyond tolerance."
        )


if __name__ == "__main__":
    main()
