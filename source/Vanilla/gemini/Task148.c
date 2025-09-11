#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure for a stack node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Structure for the stack
typedef struct Stack {
    Node* top;
} Stack;


// Function to create a new stack
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}


// Function to check if the stack is empty
bool isEmpty(Stack* stack) {
    return stack->top == NULL;
}

// Function to push an element onto the stack
void push(Stack* stack, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Function to pop an element from the stack
int pop(Stack* stack) {
    if (isEmpty(stack)) {
         perror("Stack is empty");
         exit(EXIT_FAILURE);
    }
    Node* temp = stack->top;
    int value = temp->data;
    stack->top = temp->next;
    free(temp);
    return value;
}

// Function to peek at the top element of the stack
int peek(Stack* stack) {
    if (isEmpty(stack)) {
         perror("Stack is empty");
         exit(EXIT_FAILURE);
    }
    return stack->top->data;
}


int main() {
    Stack* stack = createStack();
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    printf("%d\n", peek(stack)); // Output: 30
    printf("%d\n", pop(stack)); // Output: 30
    printf("%d\n", pop(stack)); // Output: 20
    printf("%s\n", isEmpty(stack) ? "true" : "false"); // Output: false
    pop(stack);
    printf("%s\n", isEmpty(stack) ? "true" : "false"); // Output: true


    Stack* stack2 = createStack();
    printf("%s\n", isEmpty(stack2) ? "true" : "false"); // Output: true
    push(stack2, 1);
    printf("%d\n", peek(stack2)); // Output: 1
    push(stack2, 2);
    printf("%d\n", peek(stack2)); // Output: 2
    push(stack2, 3);
    printf("%d\n", peek(stack2)); // Output: 3
    printf("%d\n", pop(stack2)); // Output: 3
    printf("%d\n", pop(stack2)); // Output: 2
    printf("%d\n", pop(stack2)); // Output: 1
    printf("%s\n", isEmpty(stack2) ? "true" : "false"); // Output: true

    Stack* stack3 = createStack();
    // pop(stack3); // This will cause the program to exit with an error message: "Stack is empty"

    Stack* stack4 = createStack();
    push(stack4, 5);
    printf("%d\n", peek(stack4)); // Output: 5
    push(stack4, 6);
    printf("%d\n", peek(stack4)); // Output: 6
    pop(stack4);
    printf("%d\n", peek(stack4)); // Output: 5

    Stack* stack5 = createStack();
    push(stack5, 100);
    push(stack5, 200);
    pop(stack5);
    push(stack5, 300);
    printf("%d\n", peek(stack5)); // Output: 300
    printf("%d\n", pop(stack5)); // Output: 300
    printf("%d\n", pop(stack5)); // Output: 100

    return 0;
}