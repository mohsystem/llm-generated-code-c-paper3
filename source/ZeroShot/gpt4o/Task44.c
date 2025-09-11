#include <stdio.h>
#include <string.h>
#include <ctype.h>

int safe_operation(const char *userInput) {
    if (is_valid_input(userInput)) {
        return atoi(userInput) * 2;
    } else {
        return -1; // Invalid input
    }
}

int is_valid_input(const char *input) {
    for (int i = 0; i < strlen(input); i++) {
        if (!isdigit(input[i])) {
            return 0; // false
        }
    }
    return 1; // true
}

int main() {
    // Test cases
    printf("%d\n", safe_operation("123"));
    printf("%d\n", safe_operation("456"));
    printf("%d\n", safe_operation("hello"));
    printf("%d\n", safe_operation("789"));
    printf("%d\n", safe_operation("0"));

    return 0;
}