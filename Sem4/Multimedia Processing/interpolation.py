
import numpy as np
import matplotlib.pyplot as plt
import csv

# 1. Create 1000x1000 matrix and save to CSV
def create_matrix_csv():
    matrix = np.zeros((1000, 1000))
    for i in range(1000):
        for j in range(1000):
            matrix[i,j] = i + j
    
    with open('matrix_output.csv', 'w', newline='') as file:
        writer = csv.writer(file)
        writer.writerows(matrix)

# 2. Draw histogram for image/matrix
def draw_histogram(image):
    plt.hist(image.ravel(), bins=256, range=(0,256))
    plt.title('Image Histogram')
    plt.xlabel('Pixel Value')
    plt.ylabel('Frequency')
    plt.show()

# 3. Get N4, ND4, N8 neighbors
def get_neighbors(image, x, y):
    height, width = image.shape
    
    # N4 neighbors (up, right, down, left)
    n4 = []
    if x > 0: n4.append(image[x-1,y])
    if y < width-1: n4.append(image[x,y+1])
    if x < height-1: n4.append(image[x+1,y])
    if y > 0: n4.append(image[x,y-1])
    
    # ND4 neighbors (diagonal)
    nd4 = []
    if x > 0 and y > 0: nd4.append(image[x-1,y-1])
    if x > 0 and y < width-1: nd4.append(image[x-1,y+1])
    if x < height-1 and y > 0: nd4.append(image[x+1,y-1])
    if x < height-1 and y < width-1: nd4.append(image[x+1,y+1])
    
    # N8 = N4 + ND4
    n8 = n4 + nd4
    
    return {'N4': n4, 'ND4': nd4, 'N8': n8}

# 4. Linear interpolation
def linear_interpolation(x0, y0, x1, y1, x):
    if x1 - x0 == 0:
        return y0
    return y0 + (x - x0) * (y1 - y0) / (x1 - x0)

# 5. Bilinear interpolation
def bilinear_interpolation(image, x, y):
    x1, y1 = int(x), int(y)
    x2, y2 = min(x1 + 1, image.shape[1] - 1), min(y1 + 1, image.shape[0] - 1)
    
    fx = x - x1
    fy = y - y1
    
    p1 = image[y1, x1]
    p2 = image[y1, x2]
    p3 = image[y2, x1]
    p4 = image[y2, x2]
    
    interpolated = (1 - fx) * (1 - fy) * p1 + \
                  fx * (1 - fy) * p2 + \
                  (1 - fx) * fy * p3 + \
                  fx * fy * p4
                  
    return interpolated

# 6. Nearest neighbor interpolation
def nearest_interpolation(image, x, y):
    return image[int(round(y)), int(round(x))]
