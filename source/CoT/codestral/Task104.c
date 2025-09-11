#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void handleUserInput(char* buffer, const char* userInput) {
    if (strlen(userInput) > strlen(buffer)) {
        fprintf(stderr, "User input exceeds buffer size\n");
        exit(EXIT_FAILURE);
    }

    strcpy(buffer, userInput);
}

int main() {
    char buffer[10];
    const char* testCases[] = {"Hello", "World", "C", "Coding", "Secure"};

    for (int i = 0; i < 5; i++) {
        handleUserInput(buffer, testCases[i]);
        printf("Input: %s, Buffer: %s\n", testCases[i], buffer);
    }

    return 0;
}