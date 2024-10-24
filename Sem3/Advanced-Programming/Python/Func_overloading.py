class Shapes:
    def area(self,x,y=None):
        if (isinstance(x, float) and y is None):
            return 3.14*x*x
        elif y is not None:
            return x*y
        else:
            return "NeverGonnaGiveYouUp";
shapes = Shapes()
print(shapes.area(5.0))
print(shapes.area(6,8))
print(shapes.area(5))