#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node* next;
};
struct Node* newnode(int data) {
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    if (!newnode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}
void Front(struct Node** head, int data) {
    struct Node* newNode = newnode(data);
    newNode->next = *head;
    *head = newNode;
}z
void Back(struct Node** head, int data) {
    struct Node* newNode = newnode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node* temp = *head;
    while (temp->next != NULL) { 
        temp = temp->next;
    }
    temp->next = newNode;
}

void DeleteFront(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }

    struct Node* temp = *head;
    *head = (*head)->next;
    printf("Deleted element: %d\n", temp->data);
    free(temp);
}

void DeleteBack(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    struct Node* temp = *head;

    if (temp->next == NULL) {
        printf("Deleted element: %d\n", temp->data);
        free(temp);
        *head = NULL;
        return;
    }

    while (temp->next->next != NULL) {
        temp = temp->next;
    }

    printf("Deleted element: %d\n", temp->next->data);
    free(temp->next);
    temp->next = NULL;
}

void display(struct Node* head) {
    if (head == NULL) {
        printf("Empty List\n");
        return;
    }

    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;

    Front(&head, 10);
    Front(&head, 20);
    Front(&head, 30);

    printf("List after inserting at the front:\n");
    display(head);

    Back(&head, 40);
    Back(&head, 50);

    printf("List after inserting at the back:\n");
    display(head);

    DeleteFront(&head);
    printf("List after deleting from the front:\n");
    display(head);

    DeleteBack(&head);
    printf("List after deleting from the back:\n");
    display(head);

    return 0;
}