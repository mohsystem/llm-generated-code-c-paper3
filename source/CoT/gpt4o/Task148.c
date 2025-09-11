#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    int *elements;
    int top;
    int capacity;
} Stack;

Stack* createStack(int size) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->capacity = size;
    stack->top = -1;
    stack->elements = (int *)malloc(stack->capacity * sizeof(int));
    return stack;
}

int push(Stack *stack, int item) {
    if (stack->top >= stack->capacity - 1) {
        return 0; // Stack Overflow
    }
    stack->elements[++stack->top] = item;
    return 1;
}

int pop(Stack *stack) {
    if (stack->top < 0) {
        return -1; // Stack Underflow
    }
    return stack->elements[stack->top--];
}

int peek(Stack *stack) {
    if (stack->top < 0) {
        return -1; // Stack is empty
    }
    return stack->elements[stack->top];
}

void freeStack(Stack *stack) {
    free(stack->elements);
    free(stack);
}

int main() {
    Stack *stack = createStack(5);

    printf("%d\n", push(stack, 1)); // 1
    printf("%d\n", push(stack, 2)); // 1
    printf("%d\n", push(stack, 3)); // 1
    printf("%d\n", push(stack, 4)); // 1
    printf("%d\n", push(stack, 5)); // 1
    printf("%d\n", push(stack, 6)); // 0 (Overflow)

    printf("%d\n", peek(stack));    // 5

    printf("%d\n", pop(stack));     // 5
    printf("%d\n", pop(stack));     // 4
    printf("%d\n", pop(stack));     // 3
    printf("%d\n", pop(stack));     // 2
    printf("%d\n", pop(stack));     // 1
    printf("%d\n", pop(stack));     // -1 (Underflow)

    freeStack(stack);

    return 0;
}