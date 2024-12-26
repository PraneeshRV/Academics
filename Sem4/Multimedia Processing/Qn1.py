#1. create a 1000x1000 matrix, add the row values and column values, and display the result in a CSV file
import random
import csv
row = int(input("Enter the no of rows : "))
col = int(input("Enter the no of columns :"))
l = []
for i in range(row):
    m = []
    for j in range(col):
        m.append(random.randint(0,255))
    l.append(m)    
for row in l:
    print(row)
sum_row = []
for row in l:
    sum_row.append(sum(row))
sum_col = []
for j in range(col):
    col_sum = 0
    for i in range(row):
        col_sum += l[i][j]
    sum_col.append(col_sum)
with open("output.csv", mode="w", newline="") as file:
    writer = csv.writer(file)
    writer.writerow(sum_row)
    writer.writerow(sum_col)