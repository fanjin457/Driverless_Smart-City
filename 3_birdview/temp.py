import cv2
import glob

# images = glob.glob('./calibration/intrinsic/1/*.jpg')
images = glob.glob('./images/origin/UXGA/*.jpg')
print('num of images:', len(images))

for fname in images:
    print(fname)
    img = cv2.imread(fname)
    img_SVGA = cv2.resize(img, (800, 600), interpolation=cv2.INTER_CUBIC)
    # cv2.imwrite(fname[:-27] + 'SVGA/SVGA_' + fname[-25:], img_SVGA)
    cv2.imwrite(fname[:-30] + 'SVGA/SVGA_' + fname[-25:], img_SVGA)