#7. bitplane extraction
import random
l = []
n = int(input("Enter the dimension of matrix:"))
for i in range(n):
    ll = []
    for j in range(n):
        ll.append(random.randint(0,255))
    l.append(ll)   
for row in l:
    print(row)    
b = []
for i in range(n):
    bb = []
    for j in range(n):
        binary = bin(l[i][j])
        bb.append(binary)
    b.append(bb)  
e = []
for i in range(n):
    ee = []
    for j in range(n):
        lastbit = b[i][j][-1] 
        ee.append(lastbit)
    e.append(ee)  
f = []
for i in range(n):
    ff = []
    for j in range(n):
        ff.append(int(e[i][j]))  
    f.append(ff)  
print("Extraction bit:\n")    
for row in f:
    print(row)