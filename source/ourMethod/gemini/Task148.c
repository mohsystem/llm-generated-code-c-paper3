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
    if (stack == NULL) {
      perror("Failed to allocate memory for stack");
      exit(EXIT_FAILURE);
    }
    stack->top = -1;
    return stack;
}

bool isEmpty(Task148* stack) {
    return stack->top == -1;
}

void push(Task148* stack, int value) {
    if (stack->top == MAX_SIZE - 1) {
         fprintf(stderr, "Stack overflow\n");
         exit(EXIT_FAILURE); // Or handle the error as needed
    }
    stack->top++;
    stack->data[stack->top] = value;
}

int pop(Task148* stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty\n");
        exit(EXIT_FAILURE); // Or handle the error as needed

    }
    int value = stack->data[stack->top];
    stack->top--;
    return value;
}

int peek(Task148* stack) {
    if (isEmpty(stack)) {
       fprintf(stderr, "Stack is empty\n");
       exit(EXIT_FAILURE); // Or handle the error as needed
    }
    return stack->data[stack->top];
}


int main() {
    Task148* stack = createStack();
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    printf("%d\n", pop(stack));  // Output: 30
    printf("%d\n", peek(stack));  // Output: 20
    push(stack, 40);
    printf("%d\n", pop(stack));  // Output: 40
    printf("%s\n", isEmpty(stack) ? "true" : "false"); // Output: false
    printf("%d\n", pop(stack)); // Output: 20
    printf("%d\n", pop(stack)); // Output: 10
    printf("%s\n", isEmpty(stack) ? "true" : "false"); // Output: true
    free(stack);
    return 0;
}