#include <stdio.h>
#include <string.h>

const char* processInput(const char* input) {
    if (input == NULL || strlen(input) == 0 || strcmp(input, " ") == 0) {
        return "Invalid input!";
    }
    static char result[100];
    snprintf(result, sizeof(result), "Processed: %s", input);
    return result;
}

int main() {
    const char* testInputs[] = {"Hello", "World", "", " ", "C"};
    for (int i = 0; i < 5; i++) {
        printf("%s\n", processInput(testInputs[i]));
    }
    return 0;
}