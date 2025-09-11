
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int maxSize;
    int* stackArray;
    int top;
} Stack;

Stack* createStack(int size) {
    if (size <= 0) {
        fprintf(stderr, "Stack size must be positive\\n");
        return NULL;
    }
    
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack) {
        fprintf(stderr, "Memory allocation failed\\n");
        return NULL;
    }
    
    stack->stackArray = (int*)malloc(size * sizeof(int));
    if (!stack->stackArray) {
        fprintf(stderr, "Memory allocation failed\\n");
        free(stack);
        return NULL;
    }
    
    stack->maxSize = size;
    stack->top = -1;
    return stack;
}

void destroyStack(Stack* stack) {
    if (stack) {
        free(stack->stackArray);
        free(stack);
    }
}

bool isEmpty(Stack* stack) {
    if (!stack) return true;
    return (stack->top == -1);
}

bool isFull(Stack* stack) {
    if (!stack) return true;
    return (stack->top == stack->maxSize - 1);
}

bool push(Stack* stack, int value) {
    if (!stack || isFull(stack)) {
        return false;
    }
    stack->stackArray[++stack->top] = value;
    return true;
}

bool pop(Stack* stack, int* value) {
    if (!stack || isEmpty(stack) || !value) {
        return false;
    }
    *value = stack->stackArray[stack->top--];
    return true;
}

bool peek(Stack* stack, int* value) {
    if (!stack || isEmpty(stack) || !value) {
        return false;
    }
    *value = stack->stackArray[stack->top];
    return true;
}

void runTests() {
    // Test case 1: Basic push and pop
    Stack* stack = createStack(5);
    int value;
    push(stack, 1);
    pop(stack, &value);
    printf("Test 1: %d\\n", value == 1);

    // Test case 2: Multiple operations
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    peek(stack, &value);
    int topValue = value;
    pop(stack, &value);
    printf("Test 2: %d\\n", topValue == 3 && value == 3);

    // Test case 3: Empty stack
    pop(stack, &value);
    pop(stack, &value);
    printf("Test 3: %d\\n", isEmpty(stack));

    // Test case 4: Full stack
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    push(stack, 4);
    push(stack, 5);
    printf("Test 4: %d\\n", isFull(stack));

    // Test case 5: Stack overflow handling
    printf("Test 5: %d\\n", !push(stack, 6));

    destroyStack(stack);
}

int main() {
    runTests();
    return 0;
}
