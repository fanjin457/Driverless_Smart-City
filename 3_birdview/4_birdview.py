import numpy as np
import cv2

'''
鸟瞰图示例
'''

# img = cv2.imread('./images/undistort/undistort_photo_19700101_001256.jpg')
img = cv2.imread('./images/undistort/SVGA/undistort_photo_19700101_000403 (2).jpg')
cv2.imshow('img', img)
cv2.waitKey(0)

H = np.loadtxt('H_SVGA.csv', dtype=np.float32, delimiter=',')
print('H:\n', H)

dst = cv2.warpPerspective(img, H, (600, 800), cv2.WARP_INVERSE_MAP+cv2.INTER_LINEAR)
dst = dst.swapaxes(1, 0)
cv2.imshow('dst', dst)
cv2.waitKey(0)