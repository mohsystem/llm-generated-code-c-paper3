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
            if (num2 == 0) {
                fprintf(stderr, "Cannot divide by zero\n");
                exit(EXIT_FAILURE);
            }
            return num1 / num2;
        default:
            fprintf(stderr, "Invalid operator. Supported operators are +, -, *, /\n");
            exit(EXIT_FAILURE);
    }
}

void test(double num1, double num2, char operator_) {
    printf("%f\n", calculate(num1, num2, operator_));
}

int main() {
    test(10, 5, '+');
    test(10, 5, '-');
    test(10, 5, '*');
    test(10, 5, '/');
    test(10, 0, '/');
    return 0;
}