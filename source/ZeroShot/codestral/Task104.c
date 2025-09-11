#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void handleUserInput(const char* input, char* buffer, size_t bufferSize) {
    if (strlen(input) > bufferSize) {
        fprintf(stderr, "Input is too large for the buffer\n");
        exit(EXIT_FAILURE);
    }

    strncpy(buffer, input, bufferSize);
}

int main() {
    char buffer[10];

    // Test cases
    const char* inputs[] = {"Hello", "World", "C", "Programming", "Secure"};

    for (size_t i = 0; i < sizeof(inputs) / sizeof(inputs[0]); i++) {
        handleUserInput(inputs[i], buffer, sizeof(buffer));
        printf("Successfully handled input: %s\n", inputs[i]);
    }

    return 0;
}