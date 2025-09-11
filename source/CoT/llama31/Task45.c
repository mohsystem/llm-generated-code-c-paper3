#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handleUserInput(const char* input) {
    if (input == NULL) {
        printf("Input is null.\n");
        return;
    }

    char* end;
    long number = strtol(input, &end, 10);
    if (*end != '\0') {
        printf("Input is not an integer.\n");
        return;
    }

    printf("Input is an integer: %ld\n", number);
    performOperations(number);
}

void performOperations(int number) {
    int result = number * 2;
    printf("Result of operation: %d\n", result);
}

int main() {
    // Test cases
    handleUserInput("10");
    handleUserInput("abc");
    handleUserInput("5.5");
    handleUserInput("");
    handleUserInput(NULL);

    return 0;
}