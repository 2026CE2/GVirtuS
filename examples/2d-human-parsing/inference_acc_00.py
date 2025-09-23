import socket
import timeit
import numpy as np
from PIL import Image
from datetime import datetime
import os
import sys
from collections import OrderedDict
sys.path.append('..')

# PyTorch includes
import torch
from torch.autograd import Variable
from torchvision import transforms
import cv2

# Custom includes
from dataloaders import custom_transforms as tr
from networks import deeplab_xception_transfer, graph
from inference_dataset import get_infernce_dataloader

import argparse
import torch.nn.functional as F
import time
import os.path as osp

# 🔹 Direct all results to demo_imgs folder
script_dir = os.path.dirname(os.path.abspath(__file__))
demo_imgs_dir = os.path.join(os.path.dirname(script_dir), "demo_imgs")

label_colours = [(0,0,0), (128,0,0), (255,0,0), (0,85,0), (170,0,51), (255,85,0),
                 (0,0,85), (0,119,221), (85,85,0), (0,85,85), (85,51,0), (52,86,128),
                 (0,128,0), (0,0,255), (51,170,221), (0,255,255), (85,255,170),
                 (170,255,85), (255,255,0), (255,170,0)]

def flip(x, dim):
    indices = [slice(None)] * x.dim()
    indices[dim] = torch.arange(x.size(dim) - 1, -1, -1,
                                dtype=torch.long, device=x.device)
    return x[tuple(indices)]

def flip_cihp(tail_list):
    tail_list_rev = [None] * 20
    for xx in range(14):
        tail_list_rev[xx] = tail_list[xx].unsqueeze(0)
    tail_list_rev[14] = tail_list[15].unsqueeze(0)
    tail_list_rev[15] = tail_list[14].unsqueeze(0)
    tail_list_rev[16] = tail_list[17].unsqueeze(0)
    tail_list_rev[17] = tail_list[16].unsqueeze(0)
    tail_list_rev[18] = tail_list[19].unsqueeze(0)
    tail_list_rev[19] = tail_list[18].unsqueeze(0)
    return torch.cat(tail_list_rev,dim=0)

def decode_labels(mask, num_images=1, num_classes=20):
    n, h, w = mask.shape
    outputs = np.zeros((num_images, h, w, 3), dtype=np.uint8)
    for i in range(num_images):
        img = Image.new('RGB', (len(mask[i, 0]), len(mask[i])))
        pixels = img.load()
        for j_, j in enumerate(mask[i, :, :]):
            for k_, k in enumerate(j):
                if k < num_classes:
                    pixels[k_, j_] = label_colours[k]
        outputs[i] = np.array(img)
    return outputs

def read_img(img_path):
    _img = Image.open(img_path).convert('RGB')
    return _img

def img_transform(img, transform=None):
    sample = {'image': img, 'label': 0}
    sample = transform(sample)
    return sample

def inference(net, img_list, opts, use_gpu=True):
    total_start = time.time()  # 🔹 Track total runtime

    # Prepare graph adjacencies
    adj2_ = torch.from_numpy(graph.cihp2pascal_nlp_adj).float()
    adj2_test = adj2_.unsqueeze(0).unsqueeze(0).expand(1, 1, 7, 20).cuda().transpose(2, 3)

    adj1_ = Variable(torch.from_numpy(graph.preprocess_adj(graph.pascal_graph)).float())
    adj3_test = adj1_.unsqueeze(0).unsqueeze(0).expand(1, 1, 7, 7).cuda()

    cihp_adj = graph.preprocess_adj(graph.cihp_graph)
    adj3_ = Variable(torch.from_numpy(cihp_adj).float())
    adj1_test = adj3_.unsqueeze(0).unsqueeze(0).expand(1, 1, 20, 20).cuda()

    inference_dataloader = get_infernce_dataloader(opts)
    total = len(inference_dataloader)

    for i_batch, data in enumerate(inference_dataloader):
        single_ss = time.time()

        testloader_list = data['testloader_list']
        testloader_flip_list = data['testloader_flip_list']
        output_path = data['output_path'][0]
        label_output_path = data['label_output_path'][0]

        # 🔹 Print image path being processed
        print(f" Processing image: {output_path}")

        for epoch in range(1):
            net.eval()

            for iii, sample_batched in enumerate(zip(testloader_list, testloader_flip_list)):
                inputs, labels = sample_batched[0]['image'], sample_batched[0]['label']
                inputs_f, _ = sample_batched[1]['image'], sample_batched[1]['label']
                inputs = torch.cat((inputs, inputs_f), dim=0)

                if iii == 0:
                    _, _, h, w = inputs.size()

                inputs = Variable(inputs, requires_grad=False)

                with torch.no_grad():
                    if use_gpu:
                        inputs = inputs.cuda()
                    outputs = net.forward(inputs, adj1_test.cuda(), adj3_test.cuda(), adj2_test.cuda())
                    outputs = (outputs[0] + flip(flip_cihp(outputs[1]), dim=-1)) / 2
                    outputs = outputs.unsqueeze(0)

                    if iii > 0:
                        outputs = F.upsample(outputs, size=(h, w), mode='bilinear', align_corners=True)
                        outputs_final = outputs_final + outputs
                    else:
                        outputs_final = outputs.clone()

            predictions = torch.max(outputs_final, 1)[1]
            results = predictions.cpu().numpy()
            vis_res = decode_labels(results)

            results = results.astype(np.uint8)
            parsing_im = Image.fromarray(vis_res[0])
            label_parsing = Image.fromarray(results[0, :, :], 'L')

            # 🔹 Save directly into demo_imgs
            img_name = os.path.basename(output_path).replace("_vis.png", "")
            parsing_save_path = os.path.join(demo_imgs_dir, f"parsed_{img_name}.png")
            label_save_path   = os.path.join(demo_imgs_dir, f"label_{img_name}.png")

            parsing_im.save(parsing_save_path)
            label_parsing.save(label_save_path)

            print(f" Saved parsing result at: {parsing_save_path}")
            print(f" Saved label result at:   {label_save_path}")

        single_ee = time.time()
        print(f"⏱️ Time for {os.path.basename(output_path)}: {single_ee - single_ss:.2f} sec")

    total_end = time.time()
    print(f"🔥 Total time for all images: {total_end - total_start:.2f} seconds")

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--loadmodel', default='', type=str)
    parser.add_argument('--img_list', default='', type=str)
    parser.add_argument('--output_dir', default='', type=str)
    parser.add_argument('--use_gpu', default=1, type=int)
    parser.add_argument('--data_root', default='', type=str)
    parser.add_argument('--phase', default='train', type=str)
    opts = parser.parse_args()

    net = deeplab_xception_transfer.deeplab_xception_transfer_projection_v3v5_more_savemem(
        n_classes=20, os=16, hidden_layers=128, source_classes=7)

    if not opts.loadmodel == '':
        x = torch.load(opts.loadmodel)
        net.load_source_model(x)
        print('✅ Loaded model:', opts.loadmodel)
    else:
        raise RuntimeError('❌ No model provided!')

    if opts.use_gpu > 0:
        net.cuda()
        use_gpu = True
    else:
        use_gpu = False
        raise RuntimeError('❌ Must use GPU!')

    if not os.path.exists(opts.output_dir):
        os.makedirs(opts.output_dir)

    file = open(osp.join(opts.data_root, opts.img_list))
    imgs = file.readlines()

    try:
        inference(net=net, img_list=imgs, opts=opts)
        print(' Inference complete!')
    finally:
        # 🔹 Always cleanup, even if crash occurs
        import gc
        torch.cuda.synchronize()
        torch.cuda.empty_cache()
        gc.collect()
        del net
        print(" GPU memory and CUDA context released.")
