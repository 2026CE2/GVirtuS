#!/bin/bash
set -e

export GVIRTUS_HOME=/opt/GVirtuS
export LD_LIBRARY_PATH=$GVIRTUS_HOME/lib:$GVIRTUS_HOME/lib/frontend:$LD_LIBRARY_PATH

echo "🚀 Running 2D-Human-Parsing inference with GVirtuS..."

cat > /opt/2D-Human-Parsing/demo_imgs/img_list.txt <<EOF
/opt/2D-Human-Parsing/demo_imgs/suit.jpg
/opt/2D-Human-Parsing/demo_imgs/skirt.jpg
/opt/2D-Human-Parsing/demo_imgs/coat.jpg
/opt/2D-Human-Parsing/demo_imgs/multiperson.jpg
EOF

cd /opt/2D-Human-Parsing/inference
LD_PRELOAD="${GVIRTUS_HOME}/lib/frontend/libcudart.so:${GVIRTUS_HOME}/lib/frontend/libcuda.so:${GVIRTUS_HOME}/lib/frontend/libcublas.so:${GVIRTUS_HOME}/lib/frontend/libcublasLt.so:${GVIRTUS_HOME}/lib/frontend/libcudnn.so:${GVIRTUS_HOME}/lib/frontend/libcufft.so:${GVIRTUS_HOME}/lib/frontend/libcurand.so:${GVIRTUS_HOME}/lib/frontend/libcusparse.so:${GVIRTUS_HOME}/lib/frontend/libcusolver.so:${GVIRTUS_HOME}/lib/frontend/libnvrtc.so" \
PYTORCH_NVML_BASED_CUDA_CHECK=1 \
TORCHINDUCTOR_FORCE_DISABLE_CACHES=1 \
CUDA_LAUNCH_BLOCKING=1 \
TORCH_USE_CUDA_DSA=1 \
TORCH_SHOW_CPP_STACKTRACES=1 \
TORCH_SHOW_MEMORY_USAGE=1 \
PYTORCH_CUDA_FUSER_DISABLE=1 \
TORCH_CUDA_DEBUG=1 \
TOKENIZERS_PARALLELISM=false \
TORCH_DISABLE_ADDR2LINE=1 \
CUDNN_LOGINFO_DBG=1 \
CUDNN_LOGWARN_DBG=1 \
CUDNN_LOGERR_DBG=1 \
CUDNN_LOGDEST_DBG=stdout \
python3 inference_acc_00.py \
  --loadmodel ../pretrained/deeplabv3plus-xception-vocNov14_20-51-38_epoch-89.pth \
  --img_list ../demo_imgs/img_list.txt \
  --output_dir ../parsing_result
