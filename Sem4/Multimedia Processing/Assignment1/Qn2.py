#2. draw a histogram for an image ( a matrix can be used)
import random
import matplotlib.pyplot as plt
r = int(input("Enter the no of rows :"))
c = int(input("Enter the no of columns :"))
l = []
for i in range(r):
    m = []
    for j in range(c):
        m.append(random.randint(0,255))
    l.append(m)
print(" the matrix :\n")
for row in l:
    print(row)
def frequency(r,c,l,n):
    f=0
    for i in range(r):
        for j in range(c):
            if l[i][j] == n:
                f = f+1
    return f  
print("frequency is :")
freq = 0
for i in range(0,256):
    freq = frequency(r,c,l,i)
    print(f"{i} : {"-"*freq}")
x = []
y = []
for i in range(256):
    x.append(i)
for i in range(256):
    freq = frequency(r,c,l,i)
    y.append(freq)
plt.plot(x,y)
plt.title("HISTOGRAM")  
plt.xlabel("X-axis")            
plt.ylabel("Y-axis")            
plt.legend()                   
plt.grid(True)
plt.show()




    