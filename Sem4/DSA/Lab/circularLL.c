    #include <stdio.h>
    #include <stdlib.h>

    struct Node {
        int data;
        struct Node* next;
    };

    struct Node* createNode(int data) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = data;
        newNode->next = NULL;
        return newNode;
    }

    struct Node* insertAtBeginning(struct Node* head, int data) {
        struct Node* newNode = createNode(data);
        if (head == NULL) {
            newNode->next = newNode;
            return newNode;
        }
        struct Node* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        newNode->next = head;
        temp->next = newNode;
        return newNode;
    }

    struct Node* insertAtEnd(struct Node* head, int data) {
        struct Node* newNode = createNode(data);
        if (head == NULL) {
            newNode->next = newNode;
            return newNode;
        }
        struct Node* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = head;
        return head;
    }

    void deleteNode(struct Node** head, int key) {
        if (*head == NULL) return;
    
        struct Node *curr = *head, *prev = NULL;
        struct Node *temp = *head;
    
        while (curr->data != key) {
            if (curr->next == *head) {
                printf("Key not found\n");
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    
        if (curr->next == curr) {
            *head = NULL;
            free(curr);
            return;
        }
    
        if (curr == *head) {
            prev = *head;
            while (prev->next != *head) {
                prev = prev->next;
            }
            *head = curr->next;
            prev->next = *head;
        } else {
            prev->next = curr->next;
        }
        free(curr);
    }

    struct Node* insertAfter(struct Node* head, int data, int after) {
        if (head == NULL) {
            printf("List is empty\n");
            return head;
        }
    
        struct Node* temp = head;
        do {
            if (temp->data == after) {
                struct Node* newNode = createNode(data);
                newNode->next = temp->next;
                temp->next = newNode;
                return head;
            }
            temp = temp->next;
        } while (temp != head);
    
        printf("Node with value %d not found\n", after);
        return head;
    }

    void deleteAfter(struct Node** head, int after) {
        if (*head == NULL) {
            printf("List is empty\n");
            return;
        }
    
        struct Node* temp = *head;
        do {
            if (temp->data == after) {
                struct Node* toDelete = temp->next;
                if (toDelete == *head) {
                    *head = toDelete->next;
                }
                temp->next = toDelete->next;
                free(toDelete);
                return;
            }
            temp = temp->next;
        } while (temp != *head);
    
        printf("Node with value %d not found\n", after);
    }

    void display(struct Node* head) {
        if (head == NULL) {
            printf("List is empty\n");
            return;
        }
        struct Node* temp = head;
        do {
            printf("%d -> ", temp->data);
            temp = temp->next;
        } while (temp != head);
        printf("\n");
    }

    int main() {
        struct Node* head = NULL;
    
        // Insert nodes
        head = insertAtEnd(head, 10);
        head = insertAtEnd(head, 20);
        head = insertAtEnd(head, 30);
        head = insertAtEnd(head, 40);

        // Display the list
        printf("Initial list: ");
        display(head);

        // Delete a node
        deleteNode(&head, 20);
        printf("After deleting 20: ");
        display(head);

        // Insert more nodes
        head = insertAtEnd(head, 50);
        display(head);

        // Insert after 30
        head = insertAfter(head, 35, 30);
        printf("After inserting 35 after 30: ");
        display(head);

        // Insert after 10
        head = insertAfter(head, 15, 10);
        printf("After inserting 15 after 10: ");
        display(head);

        // Delete node 35
        deleteNode(&head, 35);
        printf("After deleting 35: ");
        display(head);

        // Delete node 15
        deleteNode(&head, 15);
        printf("After deleting 15: ");
        display(head);

        return 0;
    }
