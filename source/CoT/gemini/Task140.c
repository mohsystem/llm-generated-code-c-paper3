#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double calculate(double num1, double num2, const char *operator) {
    if (strcmp(operator, "+") == 0) {
        return num1 + num2;
    } else if (strcmp(operator, "-") == 0) {
        return num1 - num2;
    } else if (strcmp(operator, "*") == 0) {
        return num1 * num2;
    } else if (strcmp(operator, "/") == 0) {
        if (num2 == 0) {
            fprintf(stderr, "Error: Division by zero\n");
            return NAN; // Return NaN for division by zero
        }
        return num1 / num2;
    } else {
        fprintf(stderr, "Error: Invalid operator\n");
        return NAN; // Return NaN for invalid operator

    }
}

int main() {
    printf("%f\n", calculate(5, 2, "+"));
    printf("%f\n", calculate(5, 2, "-"));
    printf("%f\n", calculate(5, 2, "*"));
    printf("%f\n", calculate(5, 2, "/"));
    printf("%f\n", calculate(5, 0, "/"));
    return 0;
}