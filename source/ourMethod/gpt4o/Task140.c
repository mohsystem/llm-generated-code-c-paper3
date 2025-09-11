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
            if (num2 != 0) {
                return num1 / num2;
            } else {
                fprintf(stderr, "Error: Division by zero\n");
                exit(EXIT_FAILURE);
            }
        default:
            fprintf(stderr, "Error: Invalid operator\n");
            exit(EXIT_FAILURE);
    }
}

int main() {
    printf("%lf\n", calculate(5, 3, '+'));
    printf("%lf\n", calculate(5, 3, '-'));
    printf("%lf\n", calculate(5, 3, '*'));
    printf("%lf\n", calculate(5, 3, '/'));
    calculate(5, 0, '/');
    return 0;
}