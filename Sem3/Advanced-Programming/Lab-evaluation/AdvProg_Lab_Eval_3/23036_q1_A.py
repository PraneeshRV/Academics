class Stack:
    def __init__(self):
        self.stack = []
        self.MaxSize = 5

    def push(self, item):
        if self.is_full():
            raise IndexError("stack is full")
        self.stack.append(item)

    def is_empty(self):
        return len(self.stack) == 0

    def size(self):
        return len(self.stack)

    def is_full(self):
        return len(self.stack) == self.MaxSize

    def pop(self):
        if self.is_empty():
            raise IndexError("stack is empty")
        return self.stack.pop();
    
    def peek(self):
        if self.is_empty():
            raise IndexError("stack is empty")
        return self.stack[-1]

s = Stack()
print(f"is the stack empty?: {s.is_empty()}")
s.push(1)
s.push(4)
s.push(3)
s.push(8)
s.push(5)
print(f"is the stack full?: {s.is_full()}")
print(f"size of the stack: {s.size()}")
s.pop()
s.push(10)
print(f"Top element: {s.peek()}")
print("below line will throw error for the stack is full")
print("----------------------------------------------------")
s.push(15)