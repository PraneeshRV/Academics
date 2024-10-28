class Stack:
    def __init__(self):
        self.stack = []

    def push(self, item):
        """Add an item to the top of the stack."""
        self.stack.append(item)

    def pop(self):
        """Remove and return the top item from the stack. Raises an exception if the stack is empty."""
        if self.is_empty():
            raise IndexError("Pop from an empty stack")
        return self.stack.pop()

    def peek(self):
        """Return the top item of the stack without removing it. Raises an exception if the stack is empty."""
        if self.is_empty():
            raise IndexError("Peek from an empty stack")
        return self.stack[-1]

    def is_empty(self):
        """Return True if the stack is empty, False otherwise."""
        return len(self.stack) == 0

    def size(self):
        """Return the number of items in the stack."""
        return len(self.stack)

# Create a stack
s = Stack()

# Push elements onto the stack
s.push(14)
s.push(03)
s.push(05)

# Get the top element
print("Top element is:", s.peek())  # Output: Top element is: 15

# Pop the top element
print("Popped element is:", s.pop())  # Output: Popped element is: 15

# Check if the stack is empty
print("Is stack empty?", s.is_empty())  # Output: Is stack empty? False

# Get the current size of the stack
print("Current size of the stack:", s.size())  # Output: Current size of the stack: 2
