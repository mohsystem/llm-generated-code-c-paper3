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
                fprintf(stderr, "Division by zero\n");
                exit(EXIT_FAILURE);
            }
        default:
            fprintf(stderr, "Invalid operator\n");
            exit(EXIT_FAILURE);
    }
}

int main() {
    printf("%f\n", calculate(10, 5, '+'));
    printf("%f\n", calculate(10, 5, '-'));
    printf("%f\n", calculate(10, 5, '*'));
    printf("%f\n", calculate(10, 5, '/'));
    printf("%f\n", calculate(10, 0, '/')); // This will exit the program with error
    return 0;
}