#include <stdio.h>
#include <stdlib.h>

double calculate(double num1, double num2, char operatorSymbol) {
    switch (operatorSymbol) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            if (num2 == 0) {
                fprintf(stderr, "Division by zero\n");
                exit(EXIT_FAILURE); // Or handle the error differently
            }
            return num1 / num2;
        default:
            fprintf(stderr, "Invalid operator\n");
            exit(EXIT_FAILURE);
    }
}

int main() {
    printf("%f\n", calculate(5, 2, '+'));
    printf("%f\n", calculate(5, 2, '-'));
    printf("%f\n", calculate(5, 2, '*'));
    printf("%f\n", calculate(5, 2, '/'));
     
     // Demonstrating error handling
    printf("%f\n", calculate(5, 0, '/'));

    return 0;
}