
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

struct Node* head = NULL;

// Create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Insert at beginning
void insertAtBeginning(int data) {
    struct Node* newNode = createNode(data);
    
    if (head == NULL) {
        head = newNode;
        head->next = head;
        head->prev = head;
        return;
    }
    
    struct Node* last = head->prev;
    
    newNode->next = head;
    newNode->prev = last;
    last->next = newNode;
    head->prev = newNode;
    head = newNode;
}

// Insert at end
void insertAtEnd(int data) {
    if (head == NULL) {
        insertAtBeginning(data);
        return;
    }
    
    struct Node* newNode = createNode(data);
    struct Node* last = head->prev;
    
    newNode->next = head;
    newNode->prev = last;
    last->next = newNode;
    head->prev = newNode;
}

// Delete from beginning
void deleteFromBeginning() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    if (head->next == head) {
        free(head);
        head = NULL;
        return;
    }
    
    struct Node* last = head->prev;
    struct Node* temp = head;
    head = head->next;
    head->prev = last;
    last->next = head;
    free(temp);
}

// Delete from end
void deleteFromEnd() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    if (head->next == head) {
        free(head);
        head = NULL;
        return;
    }
    
    struct Node* last = head->prev;
    struct Node* secondLast = last->prev;
    secondLast->next = head;
    head->prev = secondLast;
    free(last);
}

// Insert at position
void insertAtPosition(int data, int position) {
    if (position < 1) {
        printf("Invalid position\n");
        return;
    }
    
    if (position == 1) {
        insertAtBeginning(data);
        return;
    }
    
    struct Node* newNode = createNode(data);
    struct Node* current = head;
    int count = 1;
    
    do {
        if (count == position) {
            newNode->next = current;
            newNode->prev = current->prev;
            current->prev->next = newNode;
            current->prev = newNode;
            return;
        }
        current = current->next;
        count++;
    } while (current != head && count <= position);
    
    printf("Position exceeds list length\n");
    free(newNode);
}

// Delete from position
void deleteFromPosition(int position) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    if (position < 1) {
        printf("Invalid position\n");
        return;
    }
    
    if (position == 1) {
        deleteFromBeginning();
        return;
    }
    
    struct Node* current = head;
    int count = 1;
    
    do {
        if (count == position) {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            free(current);
            return;
        }
        current = current->next;
        count++;
    } while (current != head && count <= position);
    
    printf("Position exceeds list length\n");
}

// Display the list
void display() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    struct Node* current = head;
    do {
        printf("%d <-> ", current->data);
        current = current->next;
    } while (current != head);
    printf("(head)\n");
}

int main() {
    // Insert some elements
        insertAtBeginning(10);
        insertAtBeginning(20);
        insertAtEnd(30);
        insertAtEnd(40);
        
        printf("Initial list: ");
        display();
        
        // Delete some elements
        deleteFromBeginning();
        printf("After deleting from beginning: ");
        display();
        
        deleteFromEnd();
        printf("After deleting from end: ");
        display();
        
                // Insert at position 2
                insertAtPosition(25, 2);
                printf("After inserting 25 at position 2: ");
                display();
                
                // Insert at position 3
                insertAtPosition(35, 3);
                printf("After inserting 35 at position 3: ");
                display();
                
                // Delete from position 2
                deleteFromPosition(2);
                printf("After deleting from position 2: ");
                display();
                
                // Delete from position 2 again
                deleteFromPosition(2);
                printf("After deleting from position 2 again: ");
                display();
        
    return 0;
}
