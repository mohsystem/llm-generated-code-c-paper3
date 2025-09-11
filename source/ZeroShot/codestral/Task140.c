#include <stdio.h>
#include <stdlib.h>

double calculate(double num1, double num2, char operator_) {
    switch (operator_) {
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
                fprintf(stderr, "Division by zero is not allowed.\n");
                exit(EXIT_FAILURE);
            }
        default:
            fprintf(stderr, "Invalid operator. Supported operators are +, -, *, /\n");
            exit(EXIT_FAILURE);
    }
}

int main() {
    printf("%f\n", calculate(10, 5, '+')); // 15.0
    printf("%f\n", calculate(10, 5, '-')); // 5.0
    printf("%f\n", calculate(10, 5, '*')); // 50.0
    printf("%f\n", calculate(10, 5, '/')); // 2.0
    return 0;
}