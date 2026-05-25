#!/bin/bash
set -euo pipefail

apt update
apt install -y python3 python3-pip
pip3 install torch==2.8.0+cu126 torchvision --index-url https://download.pytorch.org/whl/cu126
