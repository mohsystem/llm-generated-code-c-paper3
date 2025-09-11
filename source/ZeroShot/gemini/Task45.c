#include <stdio.h>
#include <stdlib.h>

int safeIntegerInput() {
    int num;
    char buffer[256]; // Buffer for input string

    while (1) {
        printf("Enter an integer: ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            char *endptr;
            num = strtol(buffer, &endptr, 10); 
            if (*endptr == '\n' || *endptr == '\0') { // Check for valid integer input
                return num;
            } else {
                printf("Invalid input. Please enter an integer.\n");
            }
        } else {
             printf("Invalid input. Please enter an integer.\n");
            
        }
    }
}

int main() {
    int num1 = safeIntegerInput();
    int num2 = safeIntegerInput();

    if (num2 == 0) {
        fprintf(stderr, "Error: Division by zero.\n");
        return 1; // Indicate an error
    }

    int result = num1 / num2;
    printf("Result of division: %d\n", result);


    // Test cases
    int testCases[5][2] = {{10, 2}, {5, 0}, {8, 4}, {12, 3}, {7, 0}};

    for (int i = 0; i < 5; i++) {
        if (testCases[i][1] == 0) {
            fprintf(stderr, "Error: Division by zero in %d/%d\n", testCases[i][0], testCases[i][1]);
        } else {
            printf("Result of %d/%d: %d\n", testCases[i][0], testCases[i][1], testCases[i][0] / testCases[i][1]);
        }
    }

    return 0;
}