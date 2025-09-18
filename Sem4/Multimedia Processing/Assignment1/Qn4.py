#4. write a program for linear interpolation 
import random
l=[]
for i in range(2):
    m=[]
    for j in range(2):
        m.append(random.randint(0,255))
    l.append(m)
for row in l:
    print(row)        
sc = int(input("how much would you like to scale the matrix : "))
l1 = []
for i in range(sc):
    m1 = []
    for j in range(sc):
        m1.append(0)
    l1.append(m1) 
l1[0][0] = l[0][0]
l1[0][sc-1] = l[0][1]
l1[sc-1][0] = l[1][0]
l1[sc-1][sc-1] = l[1][1]
for row in l1:
    print(row)