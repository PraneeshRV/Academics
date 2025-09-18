class Person:
    # Constructor method with `self`
    def __init__(self, name, age):
        self.name = name  # `self.name` is an instance attribute
        self.age = age    # `self.age` is an instance attribute

    # Instance method using `self`
    def greet(self):
        print(f"Hello, my name is {self.name} and I am {self.age} years old.")
    
    # Another instance method that uses `self` to call `greet`
    def birthday(self):
        self.age += 1  # `self.age` is accessed and modified
        print(f"Happy Birthday, {self.name}! You are now {self.age} years old.")

# Create an instance of the `Person` class
person = Person("Alice", 30)

# Use `self` implicitly when calling methods
person.greet()       # Output: Hello, my name is Alice and I am 30 years old.
person.birthday()    # Output: Happy Birthday, Alice! You are now 31 years old.