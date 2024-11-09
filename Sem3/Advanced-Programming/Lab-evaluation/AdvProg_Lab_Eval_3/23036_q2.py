
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    
    def __str__(self):
        return f"({self.x}, {self.y})"
    
    def __eq__(self, other):
        if isinstance(other, Point):
            return self.x == other.x and self.y == other.y
        return False

class Line:
    def __init__(self, start, end):
        self.start = start
        self.end = end
    
    def __str__(self):
        return f"Line: {self.start} to {self.end}"
    
    def __add__(self, other):
        if isinstance(other, Line):
            if self.end == other.start:
                return Line(self.start, other.end)
            elif self.start == other.end:
                return Line(other.start, self.end)
            else:
               raise IndexError("both lines should have a common point at one's beginning and other's end to concatenate") 
        return None


# Create points
point_start = Point(1, 2)
point_end = Point(3, 4)
# Create lines
line1 = Line(point_start, point_end)
line2 = Line(Point(5, 6), Point(7, 8))
line3 = Line(Point(1, 2), Point(3, 4))
line4 = Line(Point(3, 4), Point(7, 8))
# Display information
print(line1)
print(line2)
# Concatenate lines
concatenated_line = line3 + line4
print(concatenated_line)
print("below line will throw error for concatenating lines with no common point")
print("-------------------------------------------------------------------------")
concatenated_line2 = line1 + line2
print(concatenated_line2)