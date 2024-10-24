# Define a class named `Car`
class Car:
    # Constructor method to initialize attributes
    def __init__(self, make, model, year):
        self.make = make
        self.model = model
        self.year = year
    
    # Method to display car information
    def display_info(self):
        print(f"{self.year} {self.make} {self.model}")
    
    # Method to start the car
    def start(self):
        print(f"{self.make} {self.model} is starting...")

# Create an instance (object) of the `Car` class
my_car = Car("Toyota", "Camry", 2020)

# Use the methods of the `Car` class
my_car.display_info()  # Output: 2020 Toyota Camry
my_car.start()         # Output: Toyota Camry is starting...
