#include <stdio.h>
#include <stdlib.h>

double performOperation(double num1, double num2, char operator) {
    switch (operator) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            if (num2 != 0)
                return num1 / num2;
            else {
                fprintf(stderr, "Division by zero\n");
                exit(EXIT_FAILURE);
            }
        default:
            fprintf(stderr, "Invalid operator\n");
            exit(EXIT_FAILURE);
    }
}

void testCases() {
    printf("Addition: %f\n", performOperation(10, 5, '+'));
    printf("Subtraction: %f\n", performOperation(10, 5, '-'));
    printf("Multiplication: %f\n", performOperation(10, 5, '*'));
    printf("Division: %f\n", performOperation(10, 5, '/'));
    printf("Invalid Operator: %f\n", performOperation(10, 5, '%'));
}

int main() {
    testCases();
    return 0;
}