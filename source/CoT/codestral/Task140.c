#include<stdio.h>
#include<stdlib.h>

double calculate(double num1, double num2, char operator_) {
    switch (operator_) {
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
                fprintf(stderr, "Division by zero is not allowed.\n");
                exit(EXIT_FAILURE);
            }
        default:
            fprintf(stderr, "Invalid operator. Only +, -, *, / are allowed.\n");
            exit(EXIT_FAILURE);
    }
}

int main() {
    printf("%.1lf\n", calculate(10, 5, '+')); // Output: 15.0
    printf("%.1lf\n", calculate(10, 5, '-')); // Output: 5.0
    printf("%.1lf\n", calculate(10, 5, '*')); // Output: 50.0
    printf("%.1lf\n", calculate(10, 5, '/')); // Output: 2.0
    calculate(10, 0, '/'); // Prints "Division by zero is not allowed." and exits.
    calculate(10, 5, '^'); // Prints "Invalid operator. Only +, -, *, / are allowed." and exits.
    return 0;
}