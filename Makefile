.PHONY: docker-build-push-prod docker-build-gvirtus docker-build-gvirtus-pytorch run-gvirtus-backend-dev run-gvirtus-tests docker-build-openpose run-openpose-test docker-build-2d-human-parsing run-2d-human-parsing-test docker-build-pytorch-cuda-graphs run-pytorch-cuda-graphs-test run-pytorch-import-smoke-test run-simple-matrix-test

docker-build-push-prod:
	docker buildx build \
		--platform linux/amd64 \
		--push \
		--no-cache \
		-f docker/prod/Dockerfile \
		-t taslanidis/gvirtus:cuda12.6.3-cudnn-ubuntu22.04 \
		.

# Builds a base image.
docker-build-gvirtus:
	docker buildx build \
		--platform linux/amd64 \
		-f docker/dev/Dockerfile \
		-t gvirtus:cuda12.6 \
		.

# Builds a reusable PyTorch-on-GVirtuS base image so examples do not reinstall
# Python and torch on every rebuild.
docker-build-gvirtus-pytorch: docker-build-gvirtus
	docker buildx build \
		--platform linux/amd64 \
		-f examples/pytorch-cuda-graphs/Dockerfile.base \
		-t gvirtus-pytorch:cuda12.6 \
		examples/pytorch-cuda-graphs

# Runs the backend development container.
# Run docker-build-gvirtus first to build the base image.
run-gvirtus-backend-dev:
	docker run \
		--rm \
		-it \
		--network host \
		--privileged \
		-v ./etc:/opt/GVirtuS/etc/ \
		-v ./include:/opt/GVirtuS/include \
		-v ./plugins:/opt/GVirtuS/plugins \
		-v ./src:/opt/GVirtuS/src \
		-v ./docker/dev/entrypoint.sh:/entrypoint.sh \
		--entrypoint /entrypoint.sh \
		--name gvirtus-backend-dev \
		--runtime=nvidia \
		--shm-size=8G \
		gvirtus:cuda12.6

run-gvirtus-tests:
	docker exec \
		-it gvirtus-backend-dev \
		bash -c \
		'export LD_LIBRARY_PATH=$$GVIRTUS_HOME/lib/frontend:$$LD_LIBRARY_PATH && \
			cd /gvirtus/build && \
			ctest --output-on-failure'

# Build the OpenPose example.
# Run docker-build-gvirtus first to build the base image.
docker-build-openpose:
	docker buildx build \
		--platform linux/amd64 \
		-f examples/openpose/Dockerfile \
		-t openpose_gvirtus:cuda12.6 \
		examples/openpose

# Runs the OpenPose example test.
run-openpose-test: 
	docker run --rm \
		--name openpose_test_container \
		--network host \
		-v ./include:/opt/GVirtuS/include \
		-v ./plugins:/opt/GVirtuS/plugins \
		-v ./src:/opt/GVirtuS/src \
		-v ./examples/openpose/media:/opt/openpose/examples/media \
		-v ./examples/openpose:/opt/openpose/examples/gvirtus \
		-v ./etc/quic_settings.json:/opt/GVirtuS/etc/quic_settings.json \
		-v ./examples/openpose/properties.json:/opt/GVirtuS/etc/properties.json \
		-v ./etc/quic_settings.json:/opt/GVirtuS/etc/quic_settings.json \
		-v ./examples/openpose/entrypoint.sh:/entrypoint.sh \
		openpose_gvirtus:cuda12.6 \
		bash /entrypoint.sh

# Builds the 2D Human Parsing example.
# Run docker-build-gvirtus first to build the base image.
docker-build-2d-human-parsing:
	docker buildx build \
		--platform linux/amd64 \
		-f examples/2d-human-parsing/Dockerfile \
		-t human-parsing_gvirtus:cuda12.6 \
		examples/2d-human-parsing	

# Runs the 2D Human Parsing example test.
run-2d-human-parsing-test: 
	docker run --rm \
		--name human_parsing_test_container \
		--network host \
		--shm-size=8G \
		-v ./include:/opt/GVirtuS/include \
		-v ./plugins:/opt/GVirtuS/plugins \
		-v ./src:/opt/GVirtuS/src \
		-v ./examples/2d-human-parsing/inference_acc_00.py:/opt/2D-Human-Parsing/inference/inference_acc_00.py \
		-v ./examples/2d-human-parsing/demo_imgs:/opt/2D-Human-Parsing/demo_imgs \
		-v ./examples/2d-human-parsing/properties.json:/opt/GVirtuS/etc/properties.json \
		-v ./etc/quic_settings.json:/opt/GVirtuS/etc/quic_settings.json \
		-v ./examples/2d-human-parsing/entrypoint.sh:/entrypoint.sh \
		human-parsing_gvirtus:cuda12.6 \
		bash /entrypoint.sh

# Builds the PyTorch CUDA Graphs example.
# Run docker-build-gvirtus-pytorch first to build the cached PyTorch base.
docker-build-pytorch-cuda-graphs: docker-build-gvirtus-pytorch
	docker buildx build \
		--platform linux/amd64 \
		-f examples/pytorch-cuda-graphs/Dockerfile \
		-t pytorch-cuda-graphs_gvirtus:cuda12.6 \
		examples/pytorch-cuda-graphs

# Runs the PyTorch CUDA Graphs example test.
run-pytorch-cuda-graphs-test:
	docker run --rm \
		--name pytorch_cuda_graphs_test_container \
		--network host \
		--shm-size=8G \
		-e PYTORCH_CUDA_GRAPHS_BATCH_SIZE \
		-e PYTORCH_CUDA_GRAPHS_BENCHMARK_ITERS \
		-e PYTORCH_CUDA_GRAPHS_OUTPUT_JSON \
		-v ./include:/opt/GVirtuS/include \
		-v ./plugins:/opt/GVirtuS/plugins \
		-v ./src:/opt/GVirtuS/src \
		-v ./examples/pytorch-cuda-graphs:/opt/GVirtuS/examples/pytorch-cuda-graphs \
		-v ./examples/pytorch-cuda-graphs/properties.json:/opt/GVirtuS/etc/properties.json \
		-v ./etc/quic_settings.json:/opt/GVirtuS/etc/quic_settings.json \
		-v ./examples/pytorch-cuda-graphs/entrypoint.sh:/entrypoint.sh \
		pytorch-cuda-graphs_gvirtus:cuda12.6 \
		bash /entrypoint.sh

run-pytorch-import-smoke-test:
	docker run --rm \
		--name pytorch_import_smoke_test_container \
		--network host \
		--shm-size=8G \
		-e PYTORCH_CUDA_GRAPHS_MODE=import-smoke \
		-v ./include:/opt/GVirtuS/include \
		-v ./plugins:/opt/GVirtuS/plugins \
		-v ./src:/opt/GVirtuS/src \
		-v ./examples/pytorch-cuda-graphs:/opt/GVirtuS/examples/pytorch-cuda-graphs \
		-v ./examples/pytorch-cuda-graphs/properties.json:/opt/GVirtuS/etc/properties.json \
		-v ./etc/quic_settings.json:/opt/GVirtuS/etc/quic_settings.json \
		-v ./examples/pytorch-cuda-graphs/entrypoint.sh:/entrypoint.sh \
		pytorch-cuda-graphs_gvirtus:cuda12.6 \
		bash /entrypoint.sh

# Runs the simple matrix example test.
run-simple-matrix-test:
	docker run \
		--rm \
		-it \
		--name simple_matrix_test_container \
		--network host \
		-v ./include:/opt/GVirtuS/include \
		-v ./plugins:/opt/GVirtuS/plugins \
		-v ./src:/opt/GVirtuS/src \
		-v ./examples/simple_matrix/properties.json:/opt/GVirtuS/etc/properties.json \
		-v ./etc/quic_settings.json:/opt/GVirtuS/etc/quic_settings.json \
		-v ./examples/simple_matrix:/opt/GVirtuS/examples/simple_matrix \
		-v ./examples/simple_matrix/entrypoint.sh:/opt/GVirtuS/entrypoint.sh \
		gvirtus:cuda12.6 \
		bash /opt/GVirtuS/entrypoint.sh

# Simple Matrix example.
run-simple-matrix-paper-test:
	docker run \
		--rm \
		-it \
		--name simple_matrix_test_paper_container \
		--network host \
		-v ./include:/opt/GVirtuS/include \
		-v ./plugins:/opt/GVirtuS/plugins \
		-v ./src:/opt/GVirtuS/src \
		-v ./examples/simple_matrix_paper/properties.json:/opt/GVirtuS/etc/properties.json \
		-v ./etc/quic_settings.json:/opt/GVirtuS/etc/quic_settings.json \
		-v ./examples/simple_matrix_paper:/opt/GVirtuS/examples/simple_matrix_paper \
		-v ./examples/simple_matrix_paper/entrypoint.sh:/opt/GVirtuS/entrypoint.sh \
		gvirtus:cuda12.6 \
		bash /opt/GVirtuS/entrypoint.sh

# Runs the CUDA Graph API test.
run-cuda-graph-test:
	docker run \
		--rm \
		-it \
		--name cuda_graph_test_container \
		--network host \
		-v ./include:/opt/GVirtuS/include \
		-v ./plugins:/opt/GVirtuS/plugins \
		-v ./src:/opt/GVirtuS/src \
		-v ./examples/cuda_graph_test/properties.json:/opt/GVirtuS/etc/properties.json \
		-v ./examples/cuda_graph_test:/opt/GVirtuS/examples/cuda_graph_test \
		-v ./examples/cuda_graph_test/entrypoint.sh:/opt/GVirtuS/entrypoint.sh \
		gvirtus:cuda12.6 \
		bash /opt/GVirtuS/entrypoint.sh
