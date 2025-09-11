#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int performOperation(int choice, int num1, int num2) {
    switch (choice) {
        case 1:
            return num1 + num2;
        case 2:
            return num1 - num2;
        case 3:
            if (num2 == 0) {
               fprintf(stderr, "Cannot divide by zero\n");
               return -1; // Indicate an error. Consider using a different approach for error handling. 
            }
            return num1 / num2;
        case 4:
            return num1 * num2;
        default:
            fprintf(stderr, "Invalid choice\n");
            return -1; // Indicate an error
    }
}

int main() {
    int num1, num2, choice, result;

    printf("Enter first number: ");
    if (scanf("%d", &num1) != 1) {
        fprintf(stderr, "Invalid input: Please enter integers only.\n");
        return 1;
    }

    printf("Enter second number: ");
    if (scanf("%d", &num2) != 1) {
        fprintf(stderr, "Invalid input: Please enter integers only.\n");
        return 1;
    }

    printf("Enter choice (1:add, 2:subtract, 3:divide, 4:multiply): ");
    if (scanf("%d", &choice) != 1) {
        fprintf(stderr, "Invalid input: Please enter integers only.\n");
        return 1;
    }


    result = performOperation(choice, num1, num2);
    if (result != -1) { // Assuming -1 signals error from performOperation
        printf("Result: %d\n", result);
    }


    // Test cases
    printf("%d\n", performOperation(1, 10, 5)); // 15
    printf("%d\n", performOperation(2, 10, 5)); // 5
    printf("%d\n", performOperation(4, 10, 5)); // 50
    performOperation(3, 10, 0); // Cannot divide by zero
    performOperation(5, 10, 5); // Invalid choice


    return 0;
}