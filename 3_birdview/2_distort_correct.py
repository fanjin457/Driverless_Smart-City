###############################################################
#
# Refences:
# https://medium.com/@kennethjiang/calibrate-fisheye-lens-using-opencv-333b05afa0b0
# https://stackoverflow.com/questions/34316306/opencv-fisheye-calibration-cuts-too-much-of-the-resulting-image
#
###############################################################

import cv2
assert cv2.__version__[0] == '3', 'The fisheye module requires opencv version >= 3.0.0'
import numpy as np
import os
import matplotlib.pyplot as plt

'''
矫正图片
'''

#########################################################
#
#   设置去畸变后的图像大小，读取 K D
#
#########################################################

DIM=(800, 600)
# K=np.array([
#     [508.6782539205006, 0.0, 818.4325010246736], 
#     [0.0, 508.3005722134613, 601.8584017620209], 
#     [0.0, 0.0, 1.0]
# ])

# D=np.array([
#     [0.6718120200205819], 
#     [0.037783431940001326], 
#     [-0.31869396893675617], 
#     [0.14023622819406492]
# ])

K = np.loadtxt('K_SVGA.csv', dtype=np.float32, delimiter=',')
D = np.loadtxt('D_SVGA.csv', dtype=np.float32, delimiter=',')

nK = K.copy()
nK[0,0]=K[0,0]
nK[1,1]=K[1,1]

#########################################################
#
#   基于 K D 得到去畸变函数
#
#########################################################

map1, map2 = cv2.fisheye.initUndistortRectifyMap(K, D, np.eye(3), nK, DIM, cv2.CV_16SC2)

# new_K = cv2.fisheye.estimateNewCameraMatrixForUndistortRectify(K, D, DIM, np.eye(3), balance=1)
# map1, map2 = cv2.fisheye.initUndistortRectifyMap(K, D, np.eye(3), new_K, DIM, cv2.CV_16SC2)

def undistort(img_path):
    img = cv2.imread(img_path)

    if img_path[-5] == 'k':
        img += 1
    undistorted_img = cv2.remap(img, map1, map2, interpolation=cv2.INTER_LINEAR, borderMode=cv2.BORDER_CONSTANT)

    return undistorted_img

#########################################################
#
#   对示例图片做去畸变
#
#########################################################

# images = glob.glob('./calibration/1/*.jpg') + glob.glob('./calibration/2/*.jpg')
image_dir = './images/origin/SVGA/'
undistort_dir = './images/undistort/SVGA/'
birdview_dir = './images/birdview/SVGA/'
images = os.listdir(image_dir)
for p in images: 
    undistorted_img = undistort(image_dir + p)
    plt.imshow(undistorted_img[:, :, [2,1,0]])
    plt.show()
    cv2.imwrite(undistort_dir + 'undistort_' + p, undistorted_img)
