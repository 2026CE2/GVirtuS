import faulthandler
import os
import sys


faulthandler.enable(all_threads=True)

print(f"[import-smoke] python={sys.version.split()[0]} pid={os.getpid()}", flush=True)
print("[import-smoke] importing torch", flush=True)

import torch

print(f"[import-smoke] torch imported version={torch.__version__}", flush=True)
print("[import-smoke] checking torch.cuda.is_available()", flush=True)
print(f"[import-smoke] cuda_available={torch.cuda.is_available()}", flush=True)
