#3. if you give the pixel value of an image print N4, ND4, N8
import random
r = int(input("Enter the no of rows :"))
c = int(input("Enter the no of columns: "))
l = []
for i in range(r):
    m=[]
    for j in range(c):
        m.append(random.randint(0,255))
    l.append(m)
for row in l:
    print(row)    
print("")        
def neighbour(r, c, l, i, j):
    n4, nd4, n8 = [], [], []
    def is_valid(x, y):
        return 0 <= x < r and 0 <= y < c 
    if is_valid(i-1, j):  
        n4.append(l[i-1][j])
    if is_valid(i+1, j):  
        n4.append(l[i+1][j])
    if is_valid(i, j-1):  
        n4.append(l[i][j-1])
    if is_valid(i, j+1):  
        n4.append(l[i][j+1])   
    if is_valid(i-1, j-1):  
        nd4.append(l[i-1][j-1])
    if is_valid(i-1, j+1):  
        nd4.append(l[i-1][j+1])
    if is_valid(i+1, j-1):  
        nd4.append(l[i+1][j-1])
    if is_valid(i+1, j+1):  
        nd4.append(l[i+1][j+1])  
    n8 = n4 + nd4 
    print(f"n4: {n4}")
    print(f"nd4: {nd4}")
    print(f"n8: {n8}")  
x = int(input("enter the x coordinate :"))
y = int(input("Enter the y coordinate :"))
neighbour(r,c,l,x,y)


