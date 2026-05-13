.PHONY: docker-build-push-prod docker-build-gvirtus run-gvirtus-backend-dev run-gvirtus-tests docker-build-openpose run-openpose-test docker-build-2d-human-parsing run-2d-human-parsing-test run-simple-matrix-test

# ── Profiling ────────────────────────────────────────────────────────────────
# Set PROFILE=on to enable per-call CSV profiling (frontend + backend).
# CSV files land in PROFILE_DIR on the host and are mounted to /profiles inside
# each container.
#   make run-openpose-test PROFILE=on
#   make run-openpose-test PROFILE=on PROFILE_DIR=/data/profiles
PROFILE     ?= off
PROFILE_DIR ?= ./profiles

# Flags injected into every docker run / docker exec when PROFILE=on.
PROFILE_ENV   = -e GVIRTUS_PROFILE=$(PROFILE) -e GVIRTUS_PROFILE_DIR=/profiles
PROFILE_MOUNT = -v $(abspath $(PROFILE_DIR)):/profiles
# ---------------------------------------------------------------------------

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

# Runs the backend development container.
# Run docker-build-gvirtus first to build the base image.
run-gvirtus-backend-dev:
	@mkdir -p $(PROFILE_DIR)
	docker run \
		--rm \
		-it \
		--network host \
		--privileged \
		$(PROFILE_ENV) \
		$(PROFILE_MOUNT) \
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
	@mkdir -p $(PROFILE_DIR)
	docker exec \
		-it \
		$(PROFILE_ENV) \
		gvirtus-backend-dev \
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
	@mkdir -p $(PROFILE_DIR)
	docker run --rm \
		--name openpose_test_container \
		--network host \
		$(PROFILE_ENV) \
		$(PROFILE_MOUNT) \
		-v ./include:/opt/GVirtuS/include \
		-v ./plugins:/opt/GVirtuS/plugins \
		-v ./src:/opt/GVirtuS/src \
		-v ./examples/openpose/media:/opt/openpose/examples/media \
		-v ./examples/openpose:/opt/openpose/examples/gvirtus \
		-v ./etc/quic_settings.json:/opt/GVirtuS/etc/quic_settings.json \
		-v ./examples/openpose/properties.json:/opt/GVirtuS/etc/properties.json \
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
	@mkdir -p $(PROFILE_DIR)
	docker run --rm \
		--name human_parsing_test_container \
		--network host \
		--shm-size=8G \
		$(PROFILE_ENV) \
		$(PROFILE_MOUNT) \
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

# Runs the simple matrix example test.
run-simple-matrix-test:
	@mkdir -p $(PROFILE_DIR)
	docker run \
		--rm \
		-it \
		--name simple_matrix_test_container \
		--network host \
		$(PROFILE_ENV) \
		$(PROFILE_MOUNT) \
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
	@mkdir -p $(PROFILE_DIR)
	docker run \
		--rm \
		-it \
		--name simple_matrix_test_paper_container \
		--network host \
		$(PROFILE_ENV) \
		$(PROFILE_MOUNT) \
		-v ./include:/opt/GVirtuS/include \
		-v ./plugins:/opt/GVirtuS/plugins \
		-v ./src:/opt/GVirtuS/src \
		-v ./examples/simple_matrix_paper/properties.json:/opt/GVirtuS/etc/properties.json \
		-v ./etc/quic_settings.json:/opt/GVirtuS/etc/quic_settings.json \
		-v ./examples/simple_matrix_paper:/opt/GVirtuS/examples/simple_matrix_paper \
		-v ./examples/simple_matrix_paper/entrypoint.sh:/opt/GVirtuS/entrypoint.sh \
		gvirtus:cuda12.6 \
		bash /opt/GVirtuS/entrypoint.sh
