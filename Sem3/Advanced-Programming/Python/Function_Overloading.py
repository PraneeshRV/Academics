# Example of Method Overloading (Compile-time Polymorphism)
class MathOperations:
    def add(self, a, b=None, c=None):
        if b is not None and c is not None:
            return a + b + c
        elif b is not None:
            return a + b
        else:
            return a

# Create an instance of MathOperations
math_obj = MathOperations()

# Call the add method with different number of arguments
result1 = math_obj.add(1)
result2 = math_obj.add(1, 2)
result3 = math_obj.add(1, 2, 3)

print(result1)  # Output: 1
print(result2)  # Output: 3
print(result3)  # Output: 6