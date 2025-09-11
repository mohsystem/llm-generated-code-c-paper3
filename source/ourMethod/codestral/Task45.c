#include <stdio.h>
#include <stdlib.h>

double calculate(double num1, double num2, char operator) {
    switch (operator) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            if (num2 == 0) {
                fprintf(stderr, "Error: Division by zero is not allowed.\n");
                exit(EXIT_FAILURE);
            }
            return num1 / num2;
        default:
            fprintf(stderr, "Error: Invalid operator. Please use +, -, *, or /.\n");
            exit(EXIT_FAILURE);
    }
}

int main() {
    double num1, num2;
    char operator;

    printf("Enter first number: ");
    if (scanf("%lf", &num1) != 1) {
        fprintf(stderr, "Error: Invalid input. Please enter a number.\n");
        return EXIT_FAILURE;
    }

    printf("Enter second number: ");
    if (scanf(" %lf", &num2) != 1) {
        fprintf(stderr, "Error: Invalid input. Please enter a number.\n");
        return EXIT_FAILURE;
    }

    printf("Enter an operator (+, -, *, /): ");
    scanf(" %c", &operator);

    double result = calculate(num1, num2, operator);
    printf("Result: %.2lf\n", result);

    return EXIT_SUCCESS;
}