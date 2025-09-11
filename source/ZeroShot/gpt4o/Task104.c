#include <stdio.h>
#include <string.h>

void handleInput(const char* input, char* output) {
    size_t bufferSize = 10;
    strncpy(output, input, bufferSize);
    output[bufferSize] = '\0';
}

int main() {
    char output[11]; // buffer size + 1 for null terminator
    const char* testInputs[] = {"short", "a bit longer", "this input is definitely too long"};
    for (int i = 0; i < 3; ++i) {
        handleInput(testInputs[i], output);
        printf("Processed input: %s\n", output);
    }
    return 0;
}