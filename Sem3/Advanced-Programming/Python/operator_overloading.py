#Operator Overloading
class Point:
    def __init__(self,x,y):
        self.x = x
        self.y = y
    def __add__(self,other):
        return Point(self.x+other.x,self.y+other.y)

    def __mul__(self,other):
        return Point(self.x*other.x,self.y*other.y)
    
P1=Point(5,8)
P2=Point(2,5)
P3=P1+P2
print(f"({P3.x},{P3.y})")
P4=P1*P2
print(f"({P4.x},{P4.y})")