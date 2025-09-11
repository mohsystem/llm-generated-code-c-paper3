
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int maxSize;
    int* stackArray;
    int top;
} Task148;

Task148* createStack(int size) {
    if (size <= 0) {
        return NULL;
    }
    
    Task148* stack = (Task148*)malloc(sizeof(Task148));
    if (stack == NULL) {
        return NULL;
    }
    
    stack->stackArray = (int*)malloc(size * sizeof(int));
    if (stack->stackArray == NULL) {
        free(stack);
        return NULL;
    }
    
    stack->maxSize = size;
    stack->top = -1;
    return stack;
}

bool push(Task148* stack, int value) {
    if (stack == NULL || stack->top >= stack->maxSize - 1) {
        return false;
    }
    stack->stackArray[++stack->top] = value;
    return true;
}

bool pop(Task148* stack, int* value) {
    if (stack == NULL || stack->top < 0) {
        return false;
    }
    *value = stack->stackArray[stack->top--];
    return true;
}

bool peek(Task148* stack, int* value) {
    if (stack == NULL || stack->top < 0) {
        return false;
    }
    *value = stack->stackArray[stack->top];
    return true;
}

bool isEmpty(Task148* stack) {
    return (stack == NULL || stack->top == -1);
}

bool isFull(Task148* stack) {
    return (stack != NULL && stack->top == stack->maxSize - 1);
}

void destroyStack(Task148* stack) {
    if (stack != NULL) {
        free(stack->stackArray);
        free(stack);
    }
}

int main() {
    // Test case 1: Basic push and pop
    Task148* stack1 = createStack(5);
    int value;
    push(stack1, 1);
    push(stack1, 2);
    pop(stack1, &value);
    printf("Test 1: %d\\n", value == 2);
    
    // Test case 2: Peek operation
    Task148* stack2 = createStack(3);
    push(stack2, 10);
    peek(stack2, &value);
    printf("Test 2: %d\\n", value == 10);
    
    // Test case 3: Empty stack check
    Task148* stack3 = createStack(2);
    printf("Test 3: %d\\n", isEmpty(stack3));
    
    // Test case 4: Full stack check
    Task148* stack4 = createStack(2);
    push(stack4, 1);
    push(stack4, 2);
    printf("Test 4: %d\\n", isFull(stack4));
    
    // Test case 5: Error handling
    Task148* stack5 = createStack(1);
    printf("Test 5: %d\\n", !pop(stack5, &value));
    
    // Clean up
    destroyStack(stack1);
    destroyStack(stack2);
    destroyStack(stack3);
    destroyStack(stack4);
    destroyStack(stack5);
    
    return 0;
}
