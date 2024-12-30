#include <stdio.h>
#define MAX 10
int stack[MAX];
int top = -1;
void push(int item) {
    if(top >= MAX-1) {
        printf("\nStack Overflow");
        return;
    }
    stack[++top] = item;
}
int pop() {
    if(top < 0) {
        printf("\nStack Underflow");
        return -1;
    }
    return stack[top--];
}
int peek() {
    if(top < 0) {
        printf("\nStack is Empty");
        return -1;
    }
    return stack[top];
}
void display() {
    if(top < 0) {
        printf("\nStack is Empty");
        return;
    }
    printf("\nStack elements are:\n");
    for(int i = top; i >= 0; i--)
        printf("%d\n", stack[i]);
}
int main() {
push(10);
push(20);
push(30);
push(40);
push(50);
display();
    
pop();
pop();
peek();
display(); 
return 0;     
}
