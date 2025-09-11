#include <stdio.h>
#include <string.h>

const char* performOperation(int input) {
    static char result[50];
    if (input < 0) {
        return "Invalid input";
    }
    snprintf(result, sizeof(result), "Operation result: %d", input * 2);
    return result;
}

int main() {
    // Test cases for C
    printf("%s\n", performOperation(5));  // Example test case
    printf("%s\n", performOperation(-1));
    printf("%s\n", performOperation(10));
    printf("%s\n", performOperation(0));
    printf("%s\n", performOperation(100));

    return 0;
}