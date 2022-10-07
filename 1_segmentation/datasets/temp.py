import cv2
import matplotlib.pyplot as plt

mask = cv2.imread('0808_labeled/Masks/photo_19700101_000048.png')
plt.imshow(mask[:, :, [2,1,0]])
plt.show()