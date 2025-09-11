
#include <stdio.h>
#include <stdlib.h>

double calculate(double num1, double num2, char operator, int* error) {
    *error = 0;
    double result = 0;
    
    switch(operator) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if(num2 == 0) {
                *error = 1; // Division by zero error
                return 0;
            }
            result = num1 / num2;
            break;
        default:
            *error = 2; // Invalid operator error
            return 0;
    }
    return result;
}

int main() {
    int error = 0;
    double result;

    // Test cases
    result = calculate(10, 5, '+', &error);
    if(error == 0) printf("10 + 5 = %.2f\\n", result);
    else if(error == 1) printf("Error: Division by zero!\\n");
    else printf("Error: Invalid operator!\\n");

    result = calculate(10, 5, '-', &error);
    if(error == 0) printf("10 - 5 = %.2f\\n", result);
    else if(error == 1) printf("Error: Division by zero!\\n");
    else printf("Error: Invalid operator!\\n");

    result = calculate(10, 5, '*', &error);
    if(error == 0) printf("10 * 5 = %.2f\\n", result);
    else if(error == 1) printf("Error: Division by zero!\\n");
    else printf("Error: Invalid operator!\\n");

    result = calculate(10, 5, '/', &error);
    if(error == 0) printf("10 / 5 = %.2f\\n", result);
    else if(error == 1) printf("Error: Division by zero!\\n");
    else printf("Error: Invalid operator!\\n");

    result = calculate(10, 0, '/', &error);
    if(error == 0) printf("10 / 0 = %.2f\\n", result);
    else if(error == 1) printf("Error: Division by zero!\\n");
    else printf("Error: Invalid operator!\\n");

    return 0;
}
