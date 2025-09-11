
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int maxSize;
    int* stackArray;
    int top;
} Task148;

Task148* createStack(int size) {
    Task148* stack = (Task148*)malloc(sizeof(Task148));
    stack->maxSize = size;
    stack->stackArray = (int*)malloc(size * sizeof(int));
    stack->top = -1;
    return stack;
}

void destroyStack(Task148* stack) {
    free(stack->stackArray);
    free(stack);
}

bool push(Task148* stack, int value) {
    if (stack->top < stack->maxSize - 1) {
        stack->stackArray[++stack->top] = value;
        return true;
    }
    return false;
}

bool pop(Task148* stack, int* value) {
    if (stack->top >= 0) {
        *value = stack->stackArray[stack->top--];
        return true;
    }
    return false;
}

bool peek(Task148* stack, int* value) {
    if (stack->top >= 0) {
        *value = stack->stackArray[stack->top];
        return true;
    }
    return false;
}

bool isEmpty(Task148* stack) {
    return (stack->top == -1);
}

int main() {
    Task148* stack = createStack(5);
    int value;

    // Test case 1: Push elements
    push(stack, 10);
    push(stack, 20);
    peek(stack, &value);
    printf("Peek after pushing 10, 20: %d\\n", value);

    // Test case 2: Pop element
    pop(stack, &value);
    printf("Popped: %d\\n", value);
    peek(stack, &value);
    printf("Peek after pop: %d\\n", value);

    // Test case 3: Push more elements
    push(stack, 30);
    push(stack, 40);
    push(stack, 50);

    // Test case 4: Pop until empty
    while (!isEmpty(stack)) {
        pop(stack, &value);
        printf("Popped: %d\\n", value);
    }

    // Test case 5: Test error handling
    if (!pop(stack, &value)) {
        printf("Error: Stack is empty\\n");
    }

    destroyStack(stack);
    return 0;
}
