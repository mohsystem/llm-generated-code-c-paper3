#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double performOperation(double num1, double num2, const char *operatorSymbol) {
    if (strcmp(operatorSymbol, "+") == 0) {
        return num1 + num2;
    } else if (strcmp(operatorSymbol, "-") == 0) {
        return num1 - num2;
    } else if (strcmp(operatorSymbol, "*") == 0) {
        return num1 * num2;
    } else if (strcmp(operatorSymbol, "/") == 0) {
        if (num2 == 0) {
            fprintf(stderr, "Error: Division by zero\n");
            exit(EXIT_FAILURE); // Exit program to demonstrate error handling in C
        }
        return num1 / num2;
    } else {
        fprintf(stderr, "Error: Invalid operator: %s\n", operatorSymbol);
        exit(EXIT_FAILURE);
    }
}

int main() {
    double num1, num2;
    char operatorSymbol[2]; // +,-,*,/ plus null terminator

    printf("Enter first number: ");
    if (scanf("%lf", &num1) != 1) {
      fprintf(stderr, "Invalid input. Please enter a number.\n");
      return 1;
    }



    printf("Enter second number: ");
    if (scanf("%lf", &num2) != 1) {
      fprintf(stderr, "Invalid input. Please enter a number.\n");
      return 1;
    }

    printf("Enter operator (+, -, *, /): ");
    if (scanf("%1s", operatorSymbol) != 1) {
      fprintf(stderr, "Invalid input. Please enter an operator.\n");
      return 1;
    }


    if (strlen(operatorSymbol) > 1 || (strcmp(operatorSymbol, "+") != 0 && strcmp(operatorSymbol, "-") != 0 &&
        strcmp(operatorSymbol, "*") != 0 && strcmp(operatorSymbol, "/") != 0)) {

        fprintf(stderr, "Error: Invalid operator.\n");
        return 1;
    }


    double result = performOperation(num1, num2, operatorSymbol);
    printf("Result: %lf\n", result);

    // Test cases
    printf("%lf\n", performOperation(5, 2, "+")); // Expected: 7.0
    printf("%lf\n", performOperation(10, 3, "-")); // Expected: 7.0
    printf("%lf\n", performOperation(4, 6, "*")); // Expected: 24.0
    printf("%lf\n", performOperation(8, 4, "/")); // Expected: 2.0
    printf("%lf\n", performOperation(12.5, 2.5, "/")); // Expected 5.0

    return 0;
}