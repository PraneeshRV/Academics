
"""
Author: Ramaguru
Description: This script defines a SinglyLinkedList class with various operations such as inserting nodes at the beginning, end, or after a specific value. It also includes functions to find the middle node (or second middle node for even-sized lists), delete the Nth node, count nodes with values greater than a specified value, and other useful operations.
"""

class Node:
    def __init__(self, value):
        """
        Initializes a new Node with a given value.

        Parameters:
        - value: The value of the node.
        """
        self.value = value
        self.next = None

class SinglyLinkedList:
    def __init__(self):
        """Initializes an empty Singly Linked List."""
        self.head = None

    def is_empty(self):
        """
        Checks if the linked list is empty.

        Returns:
        - bool: True if the linked list is empty, False otherwise.
        """
        return self.head is None

    def insert_first(self, value):
        """
        Inserts a node with the given value at the beginning of the linked list.

        Parameters:
        - value: The value to be inserted.
        """
        new_node = Node(value)
        new_node.next = self.head
        self.head = new_node

    def insert_last(self, value):
        """
        Inserts a node with the given value at the end of the linked list.

        Parameters:
        - value: The value to be inserted.
        """
        new_node = Node(value)
        if self.is_empty():
            self.head = new_node
            return
        current = self.head
        while current.next:
            current = current.next
        current.next = new_node

    def insert_after(self, u, v):
        """
        Inserts a node with value u after a node with value v in the linked list.

        Parameters:
        - u: The value of the new node to be inserted.
        - v: The value of the existing node after which the new node should be inserted.
        """
        new_node = Node(u)
        current = self.head
        while current:
            if current.value == v:
                new_node.next = current.next
                current.next = new_node
                return
            current = current.next
        print(f"Node with value {v} not found in the linked list.")

    def insert_after_nth(self, u, N):
        """
        Inserts a node with value u after the Nth node in the linked list.

        Parameters:
        - u: The value of the new node to be inserted.
        - N: The position after which the new node should be inserted.
        """
        new_node = Node(u)
        current = self.head
        for _ in range(N - 1):
            if current:
                current = current.next
            else:
                print(f"Position {N} exceeds the length of the linked list.")
                return

        if current:
            new_node.next = current.next
            current.next = new_node
        else:
            print(f"Position {N} exceeds the length of the linked list.")

    def delete_first(self):
        """Deletes the first node of the linked list."""
        if not self.is_empty():
            self.head = self.head.next
        else:
            print("Linked list is already empty.")

    def delete_after(self, v):
        """
        Deletes the node after a node with value v in the linked list.

        Parameters:
        - v: The value of the node after which the next node should be deleted.
        """
        current = self.head
        while current:
            if current.value == v and current.next:
                current.next = current.next.next
                return
            current = current.next
        print(f"Node with value {v} not found or no node to delete after.")

    def delete_after_nth(self, N):
        """
        Deletes the node after the Nth node in the linked list.
    
        Parameters:
        - N: The position after which the next node should be deleted.
        """
        if self.is_empty() or N < 0:
            print(f"Invalid position {N}.")
            return
    
        current = self.head
        for _ in range(N - 1):
            if current and current.next:
                current = current.next
            else:
                print(f"Position {N} exceeds the length of the linked list.")
                return
    
        if current.next:
            current.next = current.next.next
        else:
            print(f"Position {N} exceeds the length of the linked list.")
        
    def display(self):
        """Displays the elements of the linked list."""
        current = self.head
        while current:
            print(current.value, end=" -> ")
            current = current.next
        print("None")


# Example usage:
linked_list = SinglyLinkedList()
linked_list.insert_last(5)
linked_list.insert_last(10)
linked_list.insert_last(15)
linked_list.insert_last(20)
linked_list.display()

linked_list.insert_first(2)
linked_list.insert_after(12, 10)
linked_list.insert_after_nth(25, 3)
linked_list.display()

linked_list.delete_first()
linked_list.display()

linked_list.delete_after(15)
linked_list.display()

linked_list.delete_after_nth(5)
linked_list.delete_after_nth(3)
linked_list.display()

linked_list.delete_after_nth(1)
linked_list.display()