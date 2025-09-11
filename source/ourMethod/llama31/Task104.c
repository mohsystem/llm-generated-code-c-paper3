#include <stdio.h>
#include <string.h>

void handleInput(const char* input, size_t bufferSize) {
    char buffer[bufferSize];

    if (strlen(input) > bufferSize - 1) { // Leave space for null terminator
        printf("Input too long. Truncating to %zu characters.\n", bufferSize - 1);
        strncpy(buffer, input, bufferSize - 1);
        buffer[bufferSize - 1] = '\0';
    } else {
        strncpy(buffer, input, bufferSize);
        buffer[bufferSize - 1] = '\0'; // Ensure null termination
    }

    printf("Buffer contents: %s\n", buffer);
}

int main() {
    // Test cases
    const char* inputs[] = {"Hello", "This is a long string that should not overflow", "Short"};

    for (size_t i = 0; i < sizeof(inputs) / sizeof(inputs[0]); i++) {
        handleInput(inputs[i], 20); // Buffer size of 20 characters
    }

    return 0;
}