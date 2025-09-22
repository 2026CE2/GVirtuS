#!/bin/bash
apt update
apt install -y nvidia-driver-570
apt update
apt install -y git
mkdir -p /gvirtus/build && cd /gvirtus/build && cmake .. && make -j$(nproc) && make install
apt install -y python3-pip python-is-python3
pip install torch torchvision networkx scipy opencv-python
cd ~
rm -rf 2D-Human-Parsing
git clone https://github.com/fyviezhao/2D-Human-Parsing
cd 2D-Human-Parsing
cp /gvirtus/examples/2d-human-parsing/deeplabv3plus-xception-vocNov14_20-51-38_epoch-89.pth ~/2D-Human-Parsing/pretrained/
cat > demo_imgs/img_list.txt <<EOF
$HOME/2D-Human-Parsing/demo_imgs/suit.jpg
$HOME/2D-Human-Parsing/demo_imgs/skirt.jpg
$HOME/2D-Human-Parsing/demo_imgs/coat.jpg
$HOME/2D-Human-Parsing/demo_imgs/multiperson.jpg
EOF
cd ~/2D-Human-Parsing/inference
#export LD_LIBRARY_PATH=${GVIRTUS_HOME}/lib/frontend:${GVIRTUS_HOME}/lib
#export GVIRTUS_LOGLEVEL=50000
LD_PRELOAD="${GVIRTUS_HOME}/lib/frontend/libcudart.so:${GVIRTUS_HOME}/lib/frontend/libcuda.so:${GVIRTUS_HOME}/lib/frontend/libcublas.so:${GVIRTUS_HOME}/lib/frontend/libcublasLt.so:${GVIRTUS_HOME}/lib/frontend/libcudnn.so:${GVIRTUS_HOME}/lib/frontend/libcufft.so:${GVIRTUS_HOME}/lib/frontend/libcurand.so:${GVIRTUS_HOME}/lib/frontend/libcusparse.so:${GVIRTUS_HOME}/lib/frontend/libcusolver.so:${GVIRTUS_HOME}/lib/frontend/libnvrtc.so" \
PYTORCH_NVML_BASED_CUDA_CHECK=1 \
TORCHINDUCTOR_FORCE_DISABLE_CACHES=1 \
CUDA_LAUNCH_BLOCKING=1 \
TORCH_USE_CUDA_DSA=1 \
TORCH_SHOW_CPP_STACKTRACES=1  \
TORCH_SHOW_MEMORY_USAGE=1 \
PYTORCH_CUDA_FUSER_DISABLE=1 \
TORCH_CUDA_DEBUG=1 \
TOKENIZERS_PARALLELISM=false \
TORCH_DISABLE_ADDR2LINE=1 \
CUDNN_LOGINFO_DBG=1 \
CUDNN_LOGWARN_DBG=1 \
CUDNN_LOGERR_DBG=1 \
CUDNN_LOGDEST_DBG=stdout \
python inference_acc.py \
--loadmodel '../pretrained/deeplabv3plus-xception-vocNov14_20-51-38_epoch-89.pth' \
--img_list ../demo_imgs/img_list.txt \
--output_dir ../parsing_result

