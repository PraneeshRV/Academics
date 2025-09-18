# 8. Embedding
import random
import csv
def embed_message(message, matrix):
    binary_message = ''.join(format(ord(char), '08b') for char in message)
    message_length = len(binary_message)
    embedded_matrix = [row[:] for row in matrix]

    message_pos = 0

    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            if message_pos < message_length:
                embedded_matrix[i][j] &= 0b11111110
                embedded_matrix[i][j] |= int(binary_message[message_pos])
                message_pos += 1
    return embedded_matrix
height = int(input("Enter the height of the matrix: "))
width = int(input("Enter the width of the matrix: "))
message = input("Enter the message to embed: ")
matrix = [[random.randrange(0, 255) for _ in range(width)] for _ in range(height)]
with open('D:\Academics\Sem4\Multimedia Processing\Assignment1\original_matrix.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerows(matrix)
embedded_matrix = embed_message(message, matrix)
with open('D:\Academics\Sem4\Multimedia Processing\Assignment1\embedded_matrix.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerows(embedded_matrix)