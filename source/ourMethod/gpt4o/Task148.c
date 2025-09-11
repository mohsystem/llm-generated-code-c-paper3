#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_MAX 100

typedef struct {
    int data[STACK_MAX];
    int top;
} Task148;

void init(Task148* stack) {
    stack->top = -1;
}

bool isEmpty(Task148* stack) {
    return stack->top == -1;
}

bool isFull(Task148* stack) {
    return stack->top == STACK_MAX - 1;
}

void push(Task148* stack, int value) {
    if (isFull(stack)) {
        fprintf(stderr, "push to full stack\n");
        exit(EXIT_FAILURE);
    }
    stack->data[++stack->top] = value;
}

int pop(Task148* stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "pop from empty stack\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top--];
}

int peek(Task148* stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "peek from empty stack\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top];
}

int main() {
    Task148 stack;
    init(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    printf("%d\n", pop(&stack)); // 30
    printf("%d\n", peek(&stack)); // 20
    printf("%d\n", pop(&stack)); // 20
    printf("%d\n", isEmpty(&stack)); // 0 (false)
    printf("%d\n", pop(&stack)); // 10

    return 0;
}