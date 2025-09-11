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
            exit(EXIT_FAILURE); // Or return an error code
        }
        return num1 / num2;
    } else {
        fprintf(stderr, "Error: Invalid operation\n");
        exit(EXIT_FAILURE); // Or return an error code
    }
}

int main() {
    int num1, num2;
    char operation[2]; // To store a single character operation and null terminator


    printf("Enter first number: ");
    if (scanf("%d", &num1) != 1) {
        fprintf(stderr, "Invalid input. Please enter numbers only.\n");
        return 1;
    }

    printf("Enter second number: ");
    if (scanf("%d", &num2) != 1) {
        fprintf(stderr, "Invalid input. Please enter numbers only.\n");
        return 1;
    }

    // Consume the newline character left by scanf
    while (getchar() != '\n');

    printf("Enter operation (+, -, *, /): ");
    fgets(operation, sizeof(operation), stdin);
    // Remove trailing newline if present
    if (operation[strlen(operation) - 1] == '\n') {
        operation[strlen(operation) - 1] = '\0';
    }

    int result = performOperation(num1, num2, operation);
    printf("Result: %d\n", result);


    // Test cases
    printf("%d\n", performOperation(5, 2, "+")); // Output: 7
    printf("%d\n", performOperation(10, 3, "-")); // Output: 7
    printf("%d\n", performOperation(4, 6, "*")); // Output: 24
    printf("%d\n", performOperation(12, 4, "/")); // Output: 3
    printf("%d\n", performOperation(8, 2, "/")); // Output: 4


    return 0;
}