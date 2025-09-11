#include <stdio.h>
#include <stdlib.h>

double calculate(double num1, double num2, char operatorr) {
    switch (operatorr) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            if (num2 == 0) {
                fprintf(stderr, "Division by zero\n");
                exit(1);
            }
            return num1 / num2;
        default:
            fprintf(stderr, "Invalid operator\n");
            exit(1);
    }
}

int main() {
    printf("%f\n", calculate(5, 2, '+'));
    printf("%f\n", calculate(5, 2, '-'));
    printf("%f\n", calculate(5, 2, '*'));
    printf("%f\n", calculate(5, 2, '/'));
    printf("%f\n", calculate(5, 0, '/')); 
    return 0;
}