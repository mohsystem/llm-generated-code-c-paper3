#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    int* elements;
    int top;
    int maxSize;
} Stack;

Stack* createStack(int size) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->elements = (int*)malloc(size * sizeof(int));
    stack->top = -1;
    stack->maxSize = size;
    return stack;
}

void push(Stack* stack, int value) {
    if (stack->top == stack->maxSize - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack->elements[++stack->top] = value;
}

int pop(Stack* stack) {
    if (stack->top == -1) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack->elements[stack->top--];
}

int peek(Stack* stack) {
    if (stack->top == -1) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->elements[stack->top];
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

int main() {
    Stack* stack = createStack(5);
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    printf("Peek: %d\n", peek(stack));  // Output: 30
    printf("Pop: %d\n", pop(stack));   // Output: 30
    printf("Peek: %d\n", peek(stack)); // Output: 20
    printf("Pop: %d\n", pop(stack));  // Output: 20
    printf("Pop: %d\n", pop(stack));  // Output: 10
    printf("Is Empty: %d\n", isEmpty(stack));  // Output: 1 (true)
    free(stack->elements);
    free(stack);
    return 0;
}