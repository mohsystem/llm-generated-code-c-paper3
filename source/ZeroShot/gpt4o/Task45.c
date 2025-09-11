#include <stdio.h>

int performOperation(int a, int b) {
    if (b == 0) {
        fprintf(stderr, "Error: Division by zero is not allowed.\n");
        return 0;
    }
    return a / b;
}

int main() {
    int a, b;
    printf("Enter two integers: ");
    if (scanf("%d %d", &a, &b) != 2) {
        fprintf(stderr, "Error: Invalid input. Please enter integers.\n");
        return 1;
    }

    printf("Result of operation: %d\n", performOperation(a, b));
    
    // Test cases
    printf("Test 1: %d\n", performOperation(10, 2));
    printf("Test 2: %d\n", performOperation(10, 0));
    printf("Test 3: %d\n", performOperation(-10, 2));
    printf("Test 4: %d\n", performOperation(10, -2));
    printf("Test 5: %d\n", performOperation(0, 1));

    return 0;
}