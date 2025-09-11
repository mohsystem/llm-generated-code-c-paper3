#include <stdio.h>

#define MAX_SIZE 5

int stack[MAX_SIZE];
int top = -1;

void push(int value) {
    if (top < MAX_SIZE - 1) {
        stack[++top] = value;
    } else {
        printf("Stack is full. Cannot push %d\n", value);
    }
}

int pop() {
    if (top >= 0) {
        return stack[top--];
    } else {
        printf("Stack is empty. Cannot pop.\n");
        return -1;
    }
}

int peek() {
    if (top >= 0) {
        return stack[top];
    } else {
        printf("Stack is empty. Cannot peek.\n");
        return -1;
    }
}

int main() {
    push(1);
    push(2);
    push(3);
    printf("%d\n", peek()); // prints 3
    printf("%d\n", pop()); // prints 3
    push(4);
    push(5);
    push(6); // prints "Stack is full. Cannot push 6"
    return 0;
}