
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int maxSize;
    int* stackArray;
    int top;
} Stack;

Stack* createStack(int size) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->maxSize = size;
    stack->stackArray = (int*)malloc(size * sizeof(int));
    stack->top = -1;
    return stack;
}

void push(Stack* stack, int value) {
    if (stack->top < stack->maxSize - 1) {
        stack->stackArray[++stack->top] = value;
    }
}

int pop(Stack* stack) {
    if (stack->top >= 0) {
        return stack->stackArray[stack->top--];
    }
    return -1;
}

int peek(Stack* stack) {
    if (stack->top >= 0) {
        return stack->stackArray[stack->top];
    }
    return -1;
}

void destroyStack(Stack* stack) {
    free(stack->stackArray);
    free(stack);
}

int main() {
    Stack* stack = createStack(5);
    
    // Test case 1: Push elements
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    printf("Peek after pushing 3 elements: %d\\n", peek(stack));  // Should print 3
    
    // Test case 2: Pop element
    printf("Popped element: %d\\n", pop(stack));  // Should print 3
    
    // Test case 3: Peek after pop
    printf("Peek after pop: %d\\n", peek(stack));  // Should print 2
    
    // Test case 4: Pop until empty
    printf("Pop: %d\\n", pop(stack));  // Should print 2
    printf("Pop: %d\\n", pop(stack));  // Should print 1
    printf("Pop empty stack: %d\\n", pop(stack));  // Should print -1
    
    // Test case 5: Push after empty
    push(stack, 5);
    printf("Peek after pushing to empty stack: %d\\n", peek(stack));  // Should print 5
    
    destroyStack(stack);
    return 0;
}
