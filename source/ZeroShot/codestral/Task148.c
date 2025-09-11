#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int maxSize;
    int top;
    int* stackArray;
} Stack;

Stack* createStack(int size) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->maxSize = size;
    stack->stackArray = (int*)malloc(sizeof(int) * size);
    stack->top = -1;
    return stack;
}

void destroyStack(Stack* stack) {
    free(stack->stackArray);
    free(stack);
}

void push(Stack* stack, int value) {
    if (stack->top < stack->maxSize - 1) {
        stack->stackArray[++stack->top] = value;
    } else {
        printf("Stack is full. Cannot push %d\n", value);
    }
}

int pop(Stack* stack) {
    if (stack->top >= 0) {
        return stack->stackArray[stack->top--];
    } else {
        printf("Stack is empty. Cannot pop.\n");
        return -1;
    }
}

int peek(Stack* stack) {
    if (stack->top >= 0) {
        return stack->stackArray[stack->top];
    } else {
        printf("Stack is empty. Cannot peek.\n");
        return -1;
    }
}

int main() {
    Stack* stack = createStack(5);
    push(stack, 1);
    push(stack, 2);
    printf("%d\n", peek(stack)); // Output: 2
    push(stack, 3);
    push(stack, 4);
    push(stack, 5);
    push(stack, 6); // Output: Stack is full. Cannot push 6
    printf("%d\n", pop(stack)); // Output: 5
    printf("%d\n", peek(stack)); // Output: 4
    destroyStack(stack);
    return 0;
}