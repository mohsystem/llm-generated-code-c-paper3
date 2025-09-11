#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int top;
} Task148;

Task148* createStack() {
    Task148* stack = (Task148*)malloc(sizeof(Task148));
    stack->top = -1;
    return stack;
}

bool isEmpty(Task148* stack) {
    return stack->top == -1;
}

void push(Task148* stack, int value) {
    if (stack->top == MAX_SIZE - 1) {
        fprintf(stderr, "Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->data[++(stack->top)] = value;
}

int pop(Task148* stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[(stack->top)--];
}

int peek(Task148* stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top];
}

int main() {
    Task148* stack = createStack();
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    printf("%d\n", peek(stack)); // Output: 3
    printf("%d\n", pop(stack));  // Output: 3
    printf("%d\n", pop(stack));  // Output: 2

    Task148* stack2 = createStack();
    printf("%s\n", isEmpty(stack2) ? "true" : "false"); // Output: true
    push(stack2, 10);
    printf("%s\n", isEmpty(stack2) ? "true" : "false"); // Output: false
    printf("%d\n", pop(stack2));  // Output: 10

    Task148 *stack3 = createStack();
    push(stack3, 5);
    push(stack3, 6);
    printf("%d\n", peek(stack3)); // Output: 6
    printf("%d\n", peek(stack3)); // Output: 6


    Task148* stack4 = createStack();
    // pop will exit if empty.
     // pop(stack4);

    Task148* stack5 = createStack();
    //peek will exit if empty
    //peek(stack5);


    free(stack);
    free(stack2);
    free(stack3);
    free(stack4);
    free(stack5);

    return 0;
}