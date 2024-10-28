class Queue:
    def __init__(self):
        self.queue = []

    def enqueue(self, item):
        self.queue.append(item)

    def dequeue(self):
        if len(self.queue) == 0:
            raise IndexError("Dequeue from an empty queue")
        return self.queue.pop(0)
    
    def front(self):
        if len(self.queue) == 0:
            raise IndexError("Peek from an empty queue")
        return self.queue[0]
    
    def is_empty(self):
        return len(self.queue) == 0
    
    def size(self):
        return len(self.queue)
    
q = Queue()
q.enqueue(15)
q.enqueue(25)
q.enqueue(50)
print(q.is_empty())
print(q.size())
print(q.front())
q.dequeue()
q.dequeue()
print(q.size())
print(q.front())
