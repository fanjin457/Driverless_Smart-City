###############################################################
#
# https://docs.opencv.org/3.4/d9/d0c/group__calib3d.html
#
###############################################################

from operator import matmul
from re import T
import cv2
assert cv2.__version__[0] == '3', 'The fisheye module requires opencv version >= 3.0.0'
import numpy as np
import matplotlib.pyplot as plt

'''
计算鸟瞰图需要的透视变换
'''

img = cv2.imread('./images/undistort/SVGA/undistort_SVGA_photo_19700101_035451.jpg')
gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)

#########################################################
#
#   检测棋盘格角点
#
#########################################################

# 检测棋盘格角点
CHECKERBOARD = (6, 9)
ret, corners = cv2.findChessboardCorners(gray, CHECKERBOARD, cv2.CALIB_CB_ADAPTIVE_THRESH + cv2.CALIB_CB_FAST_CHECK + cv2.CALIB_CB_NORMALIZE_IMAGE)

# 精确到亚像素级别
subpix_criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.1)
cv2.cornerSubPix(gray, corners, (3,3), (-1,-1), subpix_criteria)
corners = corners[:, 0, :]
print('corners.shape:', corners.shape)

# 取出四角的点
corners_4 = corners[[0, 5, 48, 53]]

# 可视化
print('corners_4.shape:', corners_4.shape)
print('corners_4:\n', corners_4)
cv2.circle(img, tuple(corners_4[0]), 5, (0, 0, 255), -1) # 红点
cv2.circle(img, tuple(corners_4[1]), 5, (0, 255, 0), -1) # 绿点
cv2.circle(img, tuple(corners_4[2]), 5, (255, 0, 0), -1) # 蓝点
cv2.circle(img, tuple(corners_4[3]), 5, (255, 255, 0), -1) # 天蓝点

plt.figure(1)
plt.imshow(img[:, :, [2,1,0]])

#########################################################
#
#   获取透视变换参数
#
#########################################################

# 设置透视变换目标点
objp_4 = np.array([
    [966, 704], 
    [846, 704], 
    [966, 896], 
    [846, 896]
], np.float32)/2
print('objp_4.shape:', objp_4.shape)
print('objp_4:\n', objp_4)

H = cv2.getPerspectiveTransform(corners_4, objp_4)
print('H:\n', H)

#########################################################
#
#   检查透视变换结果
#
#########################################################

dst = cv2.warpPerspective(img, H, (600, 800), cv2.WARP_INVERSE_MAP+cv2.INTER_LINEAR)
dst = dst.swapaxes(1, 0)

plt.figure(2)
plt.imshow(dst[:, :, [2,1,0]])
plt.show()

# np.savetxt('H_SVGA.csv', H, fmt='%.10f', delimiter=',')