#include <stdio.h>
#include <setjmp.h>
#include <string.h>

typedef struct {
    char message[50];
} Result;

Result handleInput(int a, int b) {
    Result result;
    if (b == 0) {
        strcpy(result.message, "Error: Division by zero");
    } else {
        snprintf(result.message, sizeof(result.message), "Result: %d", a / b);
    }
    return result;
}

int main() {
    Result result;

    // Test cases
    result = handleInput(10, 2);
    printf("%s\n", result.message);

    result = handleInput(10, 0);
    printf("%s\n", result.message);

    result = handleInput(-5, 3);
    printf("%s\n", result.message);

    result = handleInput(20, 4);
    printf("%s\n", result.message);

    result = handleInput(0, 1);
    printf("%s\n", result.message);

    return 0;
}