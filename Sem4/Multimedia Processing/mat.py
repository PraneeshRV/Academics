import numpy as np
from scipy.ndimage import binary_hit_or_miss, binary_dilation, binary_erosion


image = np.array([
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 1, 1, 1, 0, 1, 1, 1, 0],
    [0, 1, 1, 1, 0, 1, 1, 1, 0],
    [0, 1, 1, 1, 0, 1, 1, 1, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 1, 1, 1, 0, 1, 1, 1, 0],
    [0, 1, 1, 1, 0, 1, 1, 1, 0],
    [0, 1, 1, 1, 0, 1, 1, 1, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0]
], dtype=np.uint8)


cross_se = np.array([
    [0, 1, 0],
    [1, 1, 1],
    [0, 1, 0]
], dtype=np.uint8)


hit_or_miss_result = binary_hit_or_miss(image, structure1=cross_se)
dilated_image = binary_dilation(image, structure=cross_se)
eroded_image = binary_erosion(image, structure=cross_se)


print("Original Image:")
print(image)
print("\nHit-or-Miss Result:")
print(hit_or_miss_result.astype(int))
print("\nDilated Image:")
print(dilated_image.astype(int))
print("\nEroded Image:")
print(eroded_image.astype(int))
