#include <stdio.h>
#include <string.h>

void handleUserInput(const char* input) {
    const int bufferSize = 20; // Fixed buffer size
    char buffer[bufferSize + 1]; // +1 for null terminator

    // Securely copy input into buffer
    strncpy(buffer, input, bufferSize);
    buffer[bufferSize] = '\0'; // Ensure null termination

    // Print the buffered input
    printf("Buffered Input: %s\n", buffer);
}

int main() {
    // Test cases
    const char* inputs[] = {"Hello", "This is a test string", "Buffer overflow attempt with a very long string"};
    for (int i = 0; i < 3; i++) {
        handleUserInput(inputs[i]);
    }
    return 0;
}