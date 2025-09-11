#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int performOperation(int num1, int num2, const char *operation) {
    if (strcmp(operation, "+") == 0) {
        return num1 + num2;
    } else if (strcmp(operation, "-") == 0) {
        return num1 - num2;
    } else if (strcmp(operation, "*") == 0) {
        return num1 * num2;
    } else if (strcmp(operation, "/") == 0) {
        if (num2 == 0) {
            fprintf(stderr, "Error: Division by zero\n");
            exit(1); // Or return an error code
        }
        return num1 / num2;
    } else {
        fprintf(stderr, "Error: Invalid operation: %s\n", operation);
        exit(1); // Or return an error code

    }
}

int main() {
    int num1, num2;
    char operation[2]; // To store a single character operator

    printf("Enter first number: ");
    if (scanf("%d", &num1) != 1) {
        fprintf(stderr, "Invalid input: Please enter numbers.\n");
        return 1;
    }


    printf("Enter second number: ");
    if (scanf("%d", &num2) != 1) {
        fprintf(stderr, "Invalid input: Please enter numbers.\n");
        return 1;
    }

    printf("Enter operation (+, -, *, /): ");
    if (scanf("%1s", operation) != 1) { // Read at most 1 character
        fprintf(stderr, "Invalid input: Please enter an operation.\n");
        return 1;
    }

    int result = performOperation(num1, num2, operation);
    printf("Result: %d\n", result);


    // Test cases
    printf("%d\n", performOperation(5, 2, "+")); // 7
    printf("%d\n", performOperation(10, 3, "-")); // 7
    printf("%d\n", performOperation(4, 6, "*")); // 24
    printf("%d\n", performOperation(8, 2, "/")); // 4
    printf("%d\n", performOperation(5, 0, "/")); // Exception (program terminates)


    return 0;
}