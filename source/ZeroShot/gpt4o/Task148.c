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
    stack->top = -1;
    stack->stackArray = (int*)malloc(size * sizeof(int));
    return stack;
}

int isFull(Stack* stack) {
    return stack->top == stack->maxSize - 1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

int push(Stack* stack, int value) {
    if (isFull(stack)) {
        return 0;
    }
    stack->stackArray[++stack->top] = value;
    return 1;
}

int* pop(Stack* stack) {
    if (isEmpty(stack)) {
        return NULL;
    }
    int* value = (int*)malloc(sizeof(int));
    *value = stack->stackArray[stack->top--];
    return value;
}

int* peek(Stack* stack) {
    if (isEmpty(stack)) {
        return NULL;
    }
    int* value = (int*)malloc(sizeof(int));
    *value = stack->stackArray[stack->top];
    return value;
}

void freeStack(Stack* stack) {
    free(stack->stackArray);
    free(stack);
}

int main() {
    Stack* stack = createStack(5);
    printf("%d\n", push(stack, 10)); // 1
    printf("%d\n", push(stack, 20)); // 1
    printf("%d\n", push(stack, 30)); // 1
    int* peekValue = peek(stack);
    printf("%d\n", peekValue ? *peekValue : -1); // 30
    free(peekValue);
    int* popValue = pop(stack);
    printf("%d\n", popValue ? *popValue : -1); // 30
    free(popValue);
    popValue = pop(stack);
    printf("%d\n", popValue ? *popValue : -1); // 20
    free(popValue);
    popValue = pop(stack);
    printf("%d\n", popValue ? *popValue : -1); // 10
    free(popValue);
    popValue = pop(stack);
    printf("%d\n", popValue ? *popValue : -1); // -1
    free(popValue);
    freeStack(stack);
}