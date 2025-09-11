#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 100

// Define the stack structure for integers
typedef struct {
    int items[MAX_SIZE];
    int top;
} IntStack;

// Define the stack structure for strings
typedef struct {
    char* items[MAX_SIZE];
    int top;
} StringStack;


// Function to initialize an integer stack
void initIntStack(IntStack* stack) {
    stack->top = -1;
}

// Function to initialize a string stack
void initStringStack(StringStack* stack) {
    stack->top = -1;
}



// Function to push an integer onto the stack
bool intPush(IntStack* stack, int item) {
    if (stack->top >= MAX_SIZE - 1) {
        return false; // Stack overflow
    }
    stack->items[++(stack->top)] = item;
    return true;
}

// Function to push a string onto the stack
bool stringPush(StringStack* stack, const char* item) {
    if (stack->top >= MAX_SIZE - 1) {
        return false; // Stack overflow
    }
    stack->items[++(stack->top)] = strdup(item); // Allocate memory and copy the string
    return true;
}


// Function to pop an integer from the stack
int intPop(IntStack* stack) {
    if (stack->top == -1) {
        fprintf(stderr,"Stack is empty\n");
        exit(1);

    }
    return stack->items[(stack->top)--];
}

// Function to pop a string from the stack
char* stringPop(StringStack* stack) {
    if (stack->top == -1) {
        fprintf(stderr,"Stack is empty\n");
        exit(1);
    }
    char* item = stack->items[(stack->top)--];
    return item;
}


// Function to peek at the top element of the integer stack without popping
int intPeek(IntStack* stack) {
    if (stack->top == -1) {
                fprintf(stderr,"Stack is empty\n");
        exit(1);
    }
    return stack->items[stack->top];
}

// Function to peek at the top element of the string stack without popping
char* stringPeek(StringStack* stack) {
    if (stack->top == -1) {
                fprintf(stderr,"Stack is empty\n");
        exit(1);
    }
    return stack->items[stack->top];
}


// Function to check if the integer stack is empty
bool intIsEmpty(IntStack* stack) {
    return stack->top == -1;
}


// Function to check if the string stack is empty
bool stringIsEmpty(StringStack* stack) {
    return stack->top == -1;
}


int main() {
    IntStack intStack;
    initIntStack(&intStack);
    intPush(&intStack, 1);
    intPush(&intStack, 2);
    intPush(&intStack, 3);
    printf("%d\n", intPeek(&intStack)); // Output: 3
    printf("%d\n", intPop(&intStack)); // Output: 3
    printf("%d\n", intPop(&intStack)); // Output: 2
    printf("%s\n", intIsEmpty(&intStack) ? "true" : "false"); // Output: false
    printf("%d\n", intPop(&intStack)); // Output: 1
    printf("%s\n", intIsEmpty(&intStack) ? "true" : "false"); // Output: true



    StringStack stringStack;
    initStringStack(&stringStack);
    stringPush(&stringStack, "apple");
    stringPush(&stringStack, "banana");
    printf("%s\n", stringPeek(&stringStack));  // Output: banana
    stringPush(&stringStack, "cherry");
    printf("%s\n", stringPop(&stringStack));  // Output: cherry
    printf("%s\n", stringPop(&stringStack));  // Output: banana
    printf("%s\n", stringPop(&stringStack));  // Output: apple
    // Clean up allocated memory for strings

        free(stringStack.items[0]); // Free apple
        free(stringStack.items[1]);// Free banana
         free(stringStack.items[2]);// Free cherry

    return 0;
}