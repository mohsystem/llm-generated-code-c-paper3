#include <stdio.h>
#include <stdlib.h>

double calculate(double num1, double num2, char op) {
    switch(op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/':
            if (num2 != 0) {
                return num1 / num2;
            } else {
                fprintf(stderr, "Division by zero is not allowed.\n");
                exit(EXIT_FAILURE);
            }
        default:
            fprintf(stderr, "Invalid operator.\n");
            exit(EXIT_FAILURE);
    }
}

int main() {
    printf("%.2f\n", calculate(10, 5, '+')); // 15.00
    printf("%.2f\n", calculate(10, 5, '-')); // 5.00
    printf("%.2f\n", calculate(10, 5, '*')); // 50.00
    printf("%.2f\n", calculate(10, 5, '/')); // 2.00
    calculate(10, 0, '/'); // Error
    return 0;
}