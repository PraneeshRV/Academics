#5. write a program for bilinear interpolation 
import random
l = []
for i in range(2):
    m = []
    for j in range(2):
        m.append(random.randint(0, 255))
    l.append(m)
print("Original 2x2 matrix:")
for row in l:
    print(row)
sc = int(input("How much would you like to scale the matrix: "))
l1 = [[0 for _ in range(sc)] for _ in range(sc)]
l1[0][0] = l[0][0]
l1[0][sc-1] = l[0][1]
l1[sc-1][0] = l[1][0]
l1[sc-1][sc-1] = l[1][1]
for i in range(sc):
    for j in range(sc):
        x = i / (sc - 1)
        y = j / (sc - 1)
        l1[i][j] = int(
            l[0][0] * (1 - x) * (1 - y) +
            l[0][1] * x * (1 - y) +
            l[1][0] * (1 - x) * y +
            l[1][1] * x * y
        )
print("Scaled matrix:")
for row in l1:
    print(row)