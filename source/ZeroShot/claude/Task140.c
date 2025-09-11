
#include <stdio.h>
#include <stdlib.h>

double calculate(double num1, double num2, char operator, int* error) {
    *error = 0;
    switch(operator) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            if(num2 != 0) {
                return num1 / num2;
            } else {
                *error = 1;
                return 0;
            }
        default:
            *error = 2;
            return 0;
    }
}

int main() {
    int error;
    double result;

    result = calculate(10, 5, '+', &error);
    if(!error) printf("%.1f\\n", result);
    else printf("Error occurred\\n");

    result = calculate(10, 5, '-', &error);
    if(!error) printf("%.1f\\n", result);
    else printf("Error occurred\\n");

    result = calculate(10, 5, '*', &error);
    if(!error) printf("%.1f\\n", result);
    else printf("Error occurred\\n");

    result = calculate(10, 5, '/', &error);
    if(!error) printf("%.1f\\n", result);
    else printf("Error occurred\\n");

    result = calculate(10, 2, '*', &error);
    if(!error) printf("%.1f\\n", result);
    else printf("Error occurred\\n");

    return 0;
}
