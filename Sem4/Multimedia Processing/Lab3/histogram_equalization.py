import numpy as np
from skimage import exposure
import cv2

def euclidean_distance(x1, y1, x2, y2):
    return np.sqrt((x2-x1)**2 + (y2-y1)**2)

def city_block_distance(x1, y1, x2, y2):
    return abs(x2-x1) + abs(y2-y1)

def chessboard_distance(x1, y1, x2, y2):
    return max(abs(x2-x1), abs(y2-y1))

def iris_distance(eye_left, eye_right):
    return euclidean_distance(eye_left[0], eye_left[1], eye_right[0], eye_right[1])

def contrast_slicing(img, lower_threshold, upper_threshold, low_value, high_value):
    output = img.copy()
    output[img < lower_threshold] = low_value
    output[img > upper_threshold] = high_value
    mask = (img >= lower_threshold) & (img <= upper_threshold)
    output[mask] = (img[mask] - lower_threshold) * (high_value - low_value)/(upper_threshold - lower_threshold) + low_value
    return output

def grey_scale_slicing(img, lower_threshold, upper_threshold, background_value):
    output = np.ones_like(img) * background_value
    mask = (img >= lower_threshold) & (img <= upper_threshold)
    output[mask] = img[mask]
    return output

def histogram_matching(source_img, reference_img):
    src_hist, src_bins = np.histogram(source_img.flatten(), 256, [0,256])
    ref_hist, ref_bins = np.histogram(reference_img.flatten(), 256, [0,256])
    
    src_cdf = src_hist.cumsum()
    src_cdf_normalized = src_cdf / src_cdf.max()
    
    ref_cdf = ref_hist.cumsum()
    ref_cdf_normalized = ref_cdf / ref_cdf.max()
    
    mapping = np.zeros(256)
    for i in range(256):
        mapping[i] = np.argmin(np.abs(src_cdf_normalized[i] - ref_cdf_normalized))
    
    output = mapping[source_img]
    return output.astype(np.uint8)

if __name__ == "__main__":
    img = cv2.imread('Sem4/Multimedia Processing/Lab3/c.png', cv2.IMREAD_GRAYSCALE)
    reference = cv2.imread('Sem4/Multimedia Processing/Lab3/d.jpg', cv2.IMREAD_GRAYSCALE)
    
    dist_euclidean = euclidean_distance(0, 0, 3, 4)
    dist_cityblock = city_block_distance(0, 0, 3, 4)
    dist_chess = chessboard_distance(0, 0, 3, 4)
    
    img_contrast = contrast_slicing(img, 50, 200, 0, 255)
    img_slice = grey_scale_slicing(img, 100, 150, 0)
    img_matched = histogram_matching(img, reference)
    
    print("Euclidean distance:", dist_euclidean)
    print("City block distance:", dist_cityblock)
    print("Chessboard distance:", dist_chess)
    
    cv2.imshow('Original Image', img)
    cv2.imshow('Contrast Slicing', img_contrast)
    cv2.imshow('Grey Scale Slicing', img_slice)
    cv2.imshow('Histogram Matching', img_matched)
    cv2.waitKey(0)
    cv2.destroyAllWindows()