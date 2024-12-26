#7. bitplane extraction
import random
l = []
n = int(input("Enter the dimension of matrix:"))
for i in range(n):
    m = []
    for j in range(n):
        m.append(random.randint(0,255))
    l.append(m)   
for row in l:
    print(row)    
b = []
for i in range(n):
    b1 = []
    for j in range(n):
        binary = bin(l[i][j])
        b1.append(binary)
    b.append(b1)  
e = []
for i in range(n):
    e1 = []
    for j in range(n):
        lastbit = b[i][j][-1] 
        e1.append(lastbit)
    e.append(e1)  
f = []
for i in range(n):
    f1 = []
    for j in range(n):
        f1.append(int(e[i][j]))  
    f.append(f1)  
print("Extraction bit:\n")    
for row in f:
    print(row)