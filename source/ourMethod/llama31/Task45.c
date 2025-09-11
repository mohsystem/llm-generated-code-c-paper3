#include <stdio.h>
#include <stdlib.h>

int getInputFromUser(const char* prompt) {
    int number;
    printf("%s", prompt);
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Error: Invalid input.\n");
        exit(EXIT_FAILURE);
    }
    return number;
}

void performOperation(int number) {
    if (number == 0) {
        fprintf(stderr, "Error: Division by zero is not allowed.\n");
        return;
    }
    int result = 100 / number;
    printf("Result: %d\n", result);
}

int main() {
    const int testCases = 5;
    for (int i = 0; i < testCases; ++i) {
        int number = getInputFromUser("Enter a number: ");
        performOperation(number);
    }
    return 0;
}