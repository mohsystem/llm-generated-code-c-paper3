#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int isValidInteger(const char* input) {
    char* endptr;
    long number = strtol(input, &endptr, 10);
    if (*endptr == '\0' && number >= INT_MIN && number <= INT_MAX) {
        return 1;
    }
    return 0;
}

int isValidAge(const char* input) {
    int age = atoi(input);
    if (age >= 1 && age <= 120) {
        return 1;
    }
    return 0;
}

void validateInput(const char* input, const char* type) {
    if (strcmp(type, "integer") == 0) {
        if (isValidInteger(input)) {
            printf("Valid integer: %s\n", input);
        } else {
            printf("Invalid input. Please enter an integer.\n");
        }
    } else if (strcmp(type, "age") == 0) {
        if (isValidAge(input)) {
            printf("Valid age: %s\n", input);
        } else {
            printf("Invalid age. Please enter an age between 1 and 120.\n");
        }
    } else {
        printf("Invalid type.\n");
    }
}

int main() {
    // Test cases
    validateInput("1234", "integer");  // Valid integer
    validateInput("abcd", "integer");  // Invalid integer
    validateInput("25", "age");  // Valid age
    validateInput("150", "age");  // Invalid age
    return 0;
}