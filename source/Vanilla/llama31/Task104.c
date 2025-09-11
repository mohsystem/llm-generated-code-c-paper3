#include <stdio.h>
#include <string.h>

void handleInput(char* input, int bufferSize) {
    if (strlen(input) > bufferSize) {
        input[bufferSize] = '\0';
    }
}

int main() {
    char testCases[][50] = {"Hello", "This is a long string that should be truncated", "Short", "Very long string that will definitely overflow the buffer", "Just right"};
    char buffer[11];

    for (int i = 0; i < 5; i++) {
        strcpy(buffer, testCases[i]);
        handleInput(buffer, 10);
        printf("%s\n", buffer);
    }

    return 0;
}