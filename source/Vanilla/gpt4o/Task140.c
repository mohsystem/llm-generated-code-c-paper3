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
            if (num2 != 0) {
                return num1 / num2;
            } else {
                fprintf(stderr, "Division by zero\n");
                exit(EXIT_FAILURE);
            }
        default:
            fprintf(stderr, "Invalid operator\n");
            exit(EXIT_FAILURE);
    }
}

int main() {
    printf("%f\n", calculate(5, 3, '+'));
    printf("%f\n", calculate(5, 3, '-'));
    printf("%f\n", calculate(5, 3, '*'));
    printf("%f\n", calculate(5, 3, '/'));
    calculate(5, 0, '/');
    return 0;
}