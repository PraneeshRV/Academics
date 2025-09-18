class Stack:
    def __init__(self):
        self.stack = []
        self.max_size = 5
    def push(self, item):
        if len(self.stack)<self.max_size:
            self.stack.append(item)
        else:
            raise IndexError("Stack is full")  
    def pop(self):
        if len(self.stack)>0:
            return self.stack.pop()
        else:
            raise IndexError("stack is empty")
    def top(self):
        if len(self.stack)>0:
            return self.stack[-1]
        else:
            raise IndexError("stack is empty")
    def is_empty(self):
        return len(self.stack)==0
    def size(self):
        return len(self.stack)