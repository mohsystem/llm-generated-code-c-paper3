#include <stdio.h>
#include <stdlib.h>

double calculate(double num1, double num2, char op) {
    switch (op) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            if (num2 == 0) {
                fprintf(stderr, "Error Division by zero is not allowed.\n");
                exit(EXIT_FAILURE);
            }
            return num1 / num2;
        default:
            fprintf(stderr, "Error Incorrect Operator Value\n");
            exit(EXIT_FAILURE);
    }
}

int main() {
    // Test cases
    printf("%f\n", calculate(10, 5, '+'));  // Output: 15.000000
    printf("%f\n", calculate(12, 3, '-'));  // Output: 9.000000
    printf("%f\n", calculate(10, 5, '*'));  // Output: 50.000000
    printf("%f\n", calculate(12, 3, '/'));  // Output: 4.000000
    calculate(12, 0, '/');  // Output: Error Division by zero is not allowed.
    return 0;
}