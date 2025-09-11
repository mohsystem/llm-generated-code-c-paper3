
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    SUCCESS,
    DIVISION_BY_ZERO,
    INVALID_OPERATION
} ErrorCode;

typedef struct {
    double result;
    ErrorCode error;
    char error_message[100];
} OperationResult;

OperationResult performOperation(double num1, double num2, char operation) {
    OperationResult result = {0.0, SUCCESS, ""};
    
    switch (operation) {
        case '+':
            result.result = num1 + num2;
            break;
        case '-':
            result.result = num1 - num2;
            break;
        case '*':
            result.result = num1 * num2;
            break;
        case '/':
            if (num2 == 0) {
                result.error = DIVISION_BY_ZERO;
                strncpy(result.error_message, "Division by zero is not allowed", sizeof(result.error_message) - 1);
                return result;
            }
            result.result = num1 / num2;
            break;
        default:
            result.error = INVALID_OPERATION;
            snprintf(result.error_message, sizeof(result.error_message) - 1, 
                    "Invalid operation: %c", operation);
            return result;
    }
    return result;
}

int main() {
    // Test cases
    OperationResult result;
    
    result = performOperation(10, 5, '+');
    if (result.error == SUCCESS) {
        printf("Test 1: 10 + 5 = %.2f\\n", result.result);
    } else {
        fprintf(stderr, "Error: %s\\n", result.error_message);
    }
    
    result = performOperation(10, 5, '-');
    if (result.error == SUCCESS) {
        printf("Test 2: 10 - 5 = %.2f\\n", result.result);
    } else {
        fprintf(stderr, "Error: %s\\n", result.error_message);
    }
    
    result = performOperation(10, 5, '*');
    if (result.error == SUCCESS) {
        printf("Test 3: 10 * 5 = %.2f\\n", result.result);
    } else {
        fprintf(stderr, "Error: %s\\n", result.error_message);
    }
    
    result = performOperation(10, 5, '/');
    if (result.error == SUCCESS) {
        printf("Test 4: 10 / 5 = %.2f\\n", result.result);
    } else {
        fprintf(stderr, "Error: %s\\n", result.error_message);
    }
    
    result = performOperation(10, 0, '/');
    if (result.error == SUCCESS) {
        printf("Test 5: 10 / 0 = %.2f\\n", result.result);
    } else {
        fprintf(stderr, "Error: %s\\n", result.error_message);
    }
    
    return 0;
}
