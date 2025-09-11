#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double calculate(double num1, double num2, const char* operator) {
    double result;
    if (strcmp(operator, "+") == 0) {
        result = num1 + num2;
    } else if (strcmp(operator, "-") == 0) {
        result = num1 - num2;
    } else if (strcmp(operator, "*") == 0) {
        result = num1 * num2;
    } else if (strcmp(operator, "/") == 0) {
        if (num2 == 0) {
            fprintf(stderr, "Division by zero\n");
            exit(1); // or return a special value to indicate error.
        }
        result = num1 / num2;
    } else {
        fprintf(stderr, "Invalid operator\n");
        exit(1);
    }
    return result;
}

int main() {
    double num1, num2, result;
    char operator[2]; // sufficient to store a single character operator and null terminator.

    printf("Enter first number: ");
    scanf("%lf", &num1);

    printf("Enter operator (+, -, *, /): ");
    scanf("%1s", operator); // Read at most 1 character to prevent buffer overflow


    printf("Enter second number: ");
    scanf("%lf", &num2);

    result = calculate(num1, num2, operator);
    printf("Result: %lf\n", result);

    printf("Test cases:\n");
    printf("%lf\n", calculate(5, 2, "+"));  // Expected: 7
    printf("%lf\n", calculate(10, 4, "-")); // Expected: 6
    printf("%lf\n", calculate(3, 6, "*"));  // Expected: 18
    printf("%lf\n", calculate(8, 2, "/"));  // Expected: 4
    printf("%lf\n", calculate(20, 4, "/")); // Expected: 5

    return 0;
}