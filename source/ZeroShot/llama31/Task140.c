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
                fprintf(stderr, "Division by zero\n");
                exit(EXIT_FAILURE);
            }
        case '%':
            if (num2 != 0) {
                return (int)num1 % (int)num2;
            } else {
                fprintf(stderr, "Division by zero\n");
                exit(EXIT_FAILURE);
            }
        default:
            fprintf(stderr, "Invalid operator\n");
            exit(EXIT_FAILURE);
    }
}

void testCases() {
    printf("10 + 5 = %f\n", calculate(10, 5, '+'));
    printf("10 - 5 = %f\n", calculate(10, 5, '-'));
    printf("10 * 5 = %f\n", calculate(10, 5, '*'));
    printf("10 / 5 = %f\n", calculate(10, 5, '/'));
    printf("10 %% 5 = %f\n", calculate(10, 5, '%'));
}

int main() {
    testCases();
    return 0;
}