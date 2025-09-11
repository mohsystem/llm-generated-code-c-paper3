#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int top;
    int capacity;
} Stack;

Stack* createStack(int size) {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->elements = (int*)malloc(size * sizeof(int));
    stack->capacity = size;
    stack->top = -1;
    return stack;
}

void push(Stack *stack, int value) {
    if (stack->top == stack->capacity - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack->elements[++stack->top] = value;
}

int pop(Stack *stack) {
    if (stack->top == -1) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack->elements[stack->top--];
}

int peek(Stack *stack) {
    if (stack->top == -1) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->elements[stack->top];
}

int main() {
    Stack *stack = createStack(5);
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    push(stack, 4);
    push(stack, 5);

    printf("%d\n", pop(stack));  // 5
    printf("%d\n", peek(stack));  // 4
    push(stack, 6);
    printf("%d\n", peek(stack));  // 6
    printf("%d\n", pop(stack));  // 6

    free(stack->elements);
    free(stack);
    return 0;
}