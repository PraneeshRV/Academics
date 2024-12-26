# write a program for nearest interpolation 
import random
l = []
for i in range(2):
    m = []
    for j in range(2):
        m.append(random.randint(0, 255))
    l.append(m)

print("Original matrix:")
for row in l:
    print(row)

sc = int(input("How much would you like to scale the matrix: "))

l1 = []
for i in range(sc):
    m1 = []
    for j in range(sc):
        nearest_i = round(i * (1 / (sc - 1)))
        nearest_j = round(j * (1 / (sc - 1)))
        m1.append(l[nearest_i][nearest_j])
    l1.append(m1)
print("Scaled matrix:")
for row in l1:
    print(row)