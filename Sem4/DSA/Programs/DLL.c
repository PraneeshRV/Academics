
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
        return;
    }
    
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
}

// Insert at end
void insertAtEnd(int data) {
    struct Node* newNode = createNode(data);
    
    if (head == NULL) {
        head = newNode;
        return;
    }
    
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    temp->next = newNode;
    newNode->prev = temp;
}

// Delete from beginning
void deleteFromBeginning() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    struct Node* temp = head;
    head = head->next;
    
    if (head != NULL) {
        head->prev = NULL;
    }
    
    free(temp);
}

// Delete from end
void deleteFromEnd() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    if (head->next == NULL) {
        free(head);
        head = NULL;
        return;
    }
    
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    temp->prev->next = NULL;
    free(temp);
}

// Display the list 
void display() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    struct Node* temp = head;
    printf(" List: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Insert at a specific position
void insertAtPosition(int data, int position) {
    if (position < 1) {
        printf("Invalid position\n");
        return;
    }
    
    if (position == 1) {
        insertAtBeginning(data);
        return;
    }
    
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    
    struct Node* temp = head;
    int currentPos = 1;
    
    while (currentPos < position - 1 && temp != NULL) {
        temp = temp->next;
        currentPos++;
    }
    
    if (temp == NULL) {
        printf("Position out of range\n");
        free(newNode);
        return;
    }
    
    newNode->next = temp->next;
    newNode->prev = temp;
    
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
}

// Delete from a specific position
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
    
    struct Node* temp = head;
    int currentPos = 1;
    
    while (currentPos < position && temp != NULL) {
        temp = temp->next;
        currentPos++;
    }
    
    if (temp == NULL) {
        printf("Position out of range\n");
        return;
    }
    
    if (temp->next == NULL) {
        deleteFromEnd();
        return;
    }
    
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    free(temp);
}


int main() {
        insertAtBeginning(10);
        insertAtBeginning(20);
        insertAtBeginning(30);

        display();
        
        insertAtEnd(40);
        insertAtEnd(50);
        

        display();

        deleteFromBeginning();
        
        display();
        displayBackward();

        deleteFromEnd();
        
        display();
        
        return 0;
    
}

