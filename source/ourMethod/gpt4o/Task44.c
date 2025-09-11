#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

bool isValidInput(const char *input) {
    for (size_t i = 0; i < strlen(input); i++) {
        if (!isalnum(input[i]) && input[i] != ' ') {
            return false;
        }
    }
    return true;
}

void processInput(const char *input, char *output) {
    if (!isValidInput(input)) {
        strcpy(output, "Invalid input");
        return;
    }
    size_t i;
    for (i = 0; i < strlen(input); i++) {
        output[i] = toupper(input[i]);
    }
    output[i] = '\0';
}

int main() {
    const char *testInputs[] = {"Hello World", "Valid123", "Test Input", "Security", "CCode"};
    char output[256];
    for (size_t i = 0; i < 5; i++) {
        processInput(testInputs[i], output);
        printf("%s\n", output);
    }
    return 0;
}