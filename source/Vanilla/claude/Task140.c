
#include <stdio.h>

double calculate(double num1, double num2, char operator, int *error) {
    *error = 0;
    switch (operator) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            if (num2 != 0)
                return num1 / num2;
            *error = 1;
            return 0;
        default:
            *error = 2;
            return 0;
    }
}

int main() {
    int error;
    double result;

    // Test cases
    result = calculate(10, 5, '+', &error);
    if (!error) printf("%.2f\\n", result); // Expected: 15.00

    result = calculate(10, 5, '-', &error);
    if (!error) printf("%.2f\\n", result); // Expected: 5.00

    result = calculate(10, 5, '*', &error);
    if (!error) printf("%.2f\\n", result); // Expected: 50.00

    result = calculate(10, 5, '/', &error);
    if (!error) printf("%.2f\\n", result); // Expected: 2.00

    result = calculate(10, 0, '/', &error);
    if (error == 1) printf("Division by zero error\\n");

    return 0;
}
