#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct Stack {
    int items[MAX];
    int top;
} Stack;

void createEmptyStack(Stack* s) {
    s->top = -1;
}

void push(Stack* s, int item) {
    if (s->top == MAX - 1) {
        printf("Stack Overflow\n");
        exit(1);
    }
    s->items[++s->top] = item;
}

int pop(Stack* s) {
    if (s->top == -1) {
        printf("Stack is empty\n");
        exit(1);
    }
    return s->items[s->top--];
}

int peek(Stack* s) {
    if (s->top == -1) {
        printf("Stack is empty\n");
        exit(1);
    }
    return s->items[s->top];
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int isFull(Stack* s) {
    return s->top == MAX - 1;
}

int main() {
    Stack stack;
    createEmptyStack(&stack);
    push(&stack, 1);
    push(&stack, 2);
    push(&stack, 3);
    printf("Popped item: %d\n", pop(&stack));
    printf("Peek item: %d\n", peek(&stack));
    return 0;
}