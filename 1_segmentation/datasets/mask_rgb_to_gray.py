import cv2
import os
import numpy as np
import matplotlib.pyplot as plt

dataset_dir = './0808_labeled/'
image_dir = 'JPEGImages/'
rgb_mask_dir = 'SegmentationClass/'
gray_mask_dir = 'Masks/'

mask_list = os.listdir(dataset_dir + rgb_mask_dir)
for i in range(len(mask_list)):

    rgb_mask = cv2.imread(dataset_dir + rgb_mask_dir + mask_list[i])
    grass_layer = rgb_mask[:, :, 1] / 128
    background_layer = rgb_mask[:, :, 2] / 128
    gray_mask = grass_layer + background_layer * 2
    # plt.imshow(gray_mask, 'gray')
    # plt.show()

    cv2.imwrite(dataset_dir + gray_mask_dir + mask_list[i], gray_mask)