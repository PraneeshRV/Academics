#create a 1000x1000 matrix with random values from 0 to 255, get histogram of the matrix and plot it

import csv
import numpy as np
import random 

matrix = np.random.randint(0, 256, (1000, 1000))

histogram, bins = np.histogram(matrix.flatten(), bins=256, range=[0, 256])


import matplotlib.pyplot as plt

plt.figure(figsize=(10, 5))
plt.title('Histogram of Random Matrix')
plt.xlabel('Pixel Value')
plt.ylabel('Frequency')
plt.bar(bins[:-1], histogram, width=1, color='blue', alpha=0.7)
plt.xlim([0, 255])
plt.show()
