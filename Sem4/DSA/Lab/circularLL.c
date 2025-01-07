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
struct Node* deleteAtBeginning(struct Node* head) {
        if (head == NULL) {
            return NULL;
        }
        if (head->next == head) {
            free(head);
            return NULL;
        }
        struct Node* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        struct Node* newHead = head->next;
        temp->next = newHead;
        free(head);
        return newHead;
    }

   struct Node* deleteAtEnd(struct Node* head) {
       if (head == NULL) {
           return NULL;
       }
       if (head->next == head) {
           free(head);
           return NULL;
       }
       struct Node* temp = head;
       struct Node* prev = NULL;
       while (temp->next != head) {
           prev = temp;
           temp = temp->next;
       }
       prev->next = head;
       free(temp);
       return head;
   }

   
   struct Node* insertAtMiddle(struct Node* head, int data, int position) {
       if (position < 1) return head;
       if (position == 1) return insertAtBeginning(head, data);
       
       struct Node* newNode = createNode(data);
       struct Node* temp = head;
       for (int i = 1; i < position - 1 && temp->next != head; i++) {
           temp = temp->next;
       }
       newNode->next = temp->next;
       temp->next = newNode;
       return head;
   }
   
   struct Node* deleteAtMiddle(struct Node* head, int position) {
       if (head == NULL || position < 1) return head;
       if (position == 1) {
           struct Node* temp = head;
           while (temp->next != head) {
               temp = temp->next;
           }
           if (temp == head) {
               free(head);
               return NULL;
           }
           struct Node* newHead = head->next;
           temp->next = newHead;
           free(head);
           return newHead;
       }
       
       struct Node* temp = head;
       struct Node* prev = NULL;
       for (int i = 1; i < position && temp->next != head; i++) {
           prev = temp;
           temp = temp->next;
       }
       prev->next = temp->next;
       free(temp);
       return head;
   }
   
   void displayList(struct Node* head) {
       if (head == NULL) return;
       struct Node* temp = head;
       do {
           printf("%d -> ", temp->data);
           temp = temp->next;
       } while (temp != head);
       printf("(head)\n");
   }
   
   int main() {
       struct Node* head = NULL;
       
       // Insert some elements
       head = insertAtBeginning(head, 10);
       head = insertAtEnd(head, 20);
       head = insertAtEnd(head, 30);
       head = insertAtMiddle(head, 15, 2);
       
       printf("Initial list: ");
       displayList(head);
       
       // Delete from middle
       head = deleteAtMiddle(head, 2);
       printf("After deleting from middle: ");
       displayList(head);
       
       // Delete from end
       head = deleteAtEnd(head);
       printf("After deleting from end: ");
       displayList(head);
       
       return 0;
   }
   