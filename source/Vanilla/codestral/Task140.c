#include<stdio.h>
#include<stdexcept.h>

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
            else
                throw "Division by zero is not allowed.";
        default:
            throw "Invalid operator. Supported operators are +, -, *, /";
    }
}

int main() {
    printf("%f\n", calculate(10, 5, '+')); // Output: 15.000000
    printf("%f\n", calculate(10, 5, '-')); // Output: 5.000000
    printf("%f\n", calculate(10, 5, '*')); // Output: 50.000000
    printf("%f\n", calculate(10, 5, '/')); // Output: 2.000000
    return 0;
}