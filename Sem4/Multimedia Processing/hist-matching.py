import numpy as np
import cv2
import matplotlib.pyplot as plt

def hist_matching(source, reference):
    src_hist, _ = np.histogram(source.flatten(), 256, [0, 256])
    ref_hist, _ = np.histogram(reference.flatten(), 256, [0, 256])
    
    src_cdf = src_hist.cumsum()
    ref_cdf = ref_hist.cumsum()
    
    src_cdf_normalized = src_cdf / src_cdf.max()
    ref_cdf_normalized = ref_cdf / ref_cdf.max()
    
    lookup_table = np.zeros(256)
    j = 0
    for i in range(256):
        while j < 256 and ref_cdf_normalized[j] <= src_cdf_normalized[i]:
            j += 1
        lookup_table[i] = j-1
    
    matched = lookup_table[source]
    return matched.astype(np.uint8)

source = np.array([[50, 60, 70], 
                  [80, 90, 100], 
                  [110, 120, 130]], dtype=np.uint8)

reference = np.array([[20, 40, 60], 
                      [80, 100, 120], 
                      [140, 160, 180]], dtype=np.uint8)

matched_image = hist_matching(source, reference)

plt.figure(figsize=(15, 5))

plt.subplot(131)
plt.imshow(source, cmap='gray')
plt.title('Source Image')
plt.axis('off')

plt.subplot(132)
plt.imshow(reference, cmap='gray')
plt.title('Reference Image')
plt.axis('off')

plt.subplot(133)
plt.imshow(matched_image, cmap='gray')
plt.title('Matched Image')
plt.axis('off')

plt.tight_layout()
plt.show()

plt.figure(figsize=(15, 5))

plt.subplot(131)
plt.hist(source.flatten(), 256, [0, 256])
plt.title('Source Histogram')

plt.subplot(132)
plt.hist(reference.flatten(), 256, [0, 256])
plt.title('Reference Histogram')

plt.subplot(133)
plt.hist(matched_image.flatten(), 256, [0, 256])
plt.title('Matched Histogram')

plt.tight_layout()
plt.show()
