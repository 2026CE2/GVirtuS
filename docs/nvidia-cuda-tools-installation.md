---

# 🚀 Clean Install of NVIDIA Driver 535 + CUDA 12.2 + cuDNN 9.5.1 on Ubuntu 20.04

---

## 🔹 Step 0. If your system has broken NVIDIA/CUDA packages

First, remove everything cleanly before doing a fresh install.

### Removing all NVIDIA & CUDA packages with `dpkg` (Option 2)

Since `dpkg` does not support wildcards (`nvidia-*`), we can dynamically list and purge all NVIDIA/CUDA-related packages using `grep + awk + xargs`:

```bash
dpkg -l | grep -E "nvidia|cuda|cublas|cufft|cusolver|cusparse" | awk '{print $2}' | xargs sudo dpkg --purge --force-all
```

Then fix any broken dependencies and clean up:

```bash
sudo apt --fix-broken install -y
sudo apt-get autoremove --purge -y
sudo apt-get autoclean
sudo apt-get clean
```

Verify nothing remains:

```bash
dpkg -l | grep -E "nvidia|cuda"
```

👉 Only proceed once the output is empty.

---

## 🔹 Step 1. Verify NVIDIA driver 535 is installed

```bash
nvidia-smi
```

You should see your GPU listed with **Driver Version: 535.xx**.

If not installed, run:

```bash
sudo apt-get update
sudo apt-get install -y nvidia-driver-535 nvidia-utils-535
sudo reboot
```

---

## 🔹 Step 2. Add NVIDIA CUDA repository

```bash
wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2004/x86_64/cuda-ubuntu2004.pin
sudo mv cuda-ubuntu2004.pin /etc/apt/preferences.d/cuda-repository-pin-600

wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2004/x86_64/3bf863cc.pub
sudo apt-key add 3bf863cc.pub

sudo add-apt-repository "deb https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2004/x86_64/ /"
```

---

## 🔹 Step 3. Install CUDA 12.2 Toolkit only (no drivers!)

We don’t want CUDA to overwrite **driver 535** with a newer one (like 570).

Install just the toolkit:

```bash
sudo apt-get update
sudo apt-get install -y cuda-toolkit-12-2
```

---

## 🔹 Step 4. Add CUDA to PATH

Add the following lines to `~/.bashrc`:

```bash
export PATH=/usr/local/cuda-12.2/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/cuda-12.2/lib64:$LD_LIBRARY_PATH
```

Apply changes:

```bash
source ~/.bashrc
```

---

## 🔹 Step 5. Verify CUDA installation

```bash
nvcc --version
```

Expected → `release 12.2`

```bash
nvidia-smi
```

Expected → **Driver 535.xx, CUDA Version: 12.2**

---

# 🚀 cuDNN 9.5.1 Installation on Ubuntu 20.04

---

## 🔹 Step 1. Download cuDNN 9.5.1 repo package

```bash
wget https://developer.download.nvidia.com/compute/cudnn/9.5.1/local_installers/cudnn-local-repo-ubuntu2004-9.5.1_1.0-1_amd64.deb
```

---

## 🔹 Step 2. Install the repo package

```bash
sudo dpkg -i cudnn-local-repo-ubuntu2004-9.5.1_1.0-1_amd64.deb
```

---

## 🔹 Step 3. Add NVIDIA’s signing key

```bash
sudo cp /var/cudnn-local-repo-ubuntu2004-9.5.1/cudnn-*-keyring.gpg /usr/share/keyrings/
```

---

## 🔹 Step 4. Update APT sources

```bash
sudo apt-get update
```

---

## 🔹 Step 5. Install cuDNN 9.5.1 (runtime + dev + headers)

⚠️ Important: If you had other cuDNN repos (like 9.7 or 9.13), purge them first — otherwise `apt-get install cudnn` will install the latest.

Correct install:

```bash
sudo apt-get -y install cudnn
```

---

## 🔹 Step 6. Verify cuDNN installation

```bash
cat /usr/include/cudnn_version.h | grep CUDNN_MAJOR -A 2
```

Expected:

```
#define CUDNN_MAJOR 9
#define CUDNN_MINOR 5
#define CUDNN_PATCHLEVEL 1
```

---

✅ Done! You now have:

* **NVIDIA driver 535**
* **CUDA 12.2 Toolkit**
* **cuDNN 9.5.1**

