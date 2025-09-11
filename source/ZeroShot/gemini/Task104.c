#include <stdio.h>
#include <string.h>

void handleInput(char *input, int bufferSize, char *output) {
    if (strlen(input) > bufferSize) {
        strncpy(output, input, bufferSize);
        output[bufferSize] = '\0';
    } else {
        strcpy(output, input);
    }
}

int main() {
    char input[100];
    char output[26]; 
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // Remove trailing newline
    handleInput(input, 10, output);
    printf("%s\n", output);

    handleInput("This is a test string", 20, output);
    printf("%s\n", output);

    handleInput("Another test string", 10, output);
    printf("%s\n", output);
    
    handleInput("Short string", 20, output);
    printf("%s\n", output);

    handleInput("A very long string that exceeds the buffer size", 25, output);
    printf("%s\n", output);

    return 0;
}