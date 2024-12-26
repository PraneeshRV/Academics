#create a 1000x1000 matrix with a function, update values using rand, get sum of specific row and sum of specific column upload it to a csv file\

import numpy as np 
import random
import csv
def create_matrix(rows, cols):
    matrix = np.zeros((rows, cols))
    return matrix
def update_matrix(matrix):
    for i in range(matrix.shape[0]):
        for j in range(matrix.shape[1]):
            matrix[i, j] = random.randint(0, 100)
    return matrix
def sum_row(matrix, row):
    return np.sum(matrix[row])
def sum_col(matrix, col):
    return np.sum(matrix[:, col])
def write_to_csv(matrix):
    with open('matrix.csv', 'w', newline='') as file:
        writer = csv.writer(file)
        writer.writerows(matrix)
        matrix = create_matrix(1000, 1000)
        update_matrix(matrix)
        sum_row_10 = sum_row(matrix, 10)
        sum_col_10 = sum_col(matrix, 10)
        print('Sum of row 10:', sum_row_10)
        print('Sum of col 10:', sum_col_10)
        write_to_csv(matrix)
        print('Matrix written to matrix.csv')
        print('Done')