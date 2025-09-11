#include <stdio.h>
#include <string.h>

void handleInput(const char* input, char* output) {
    // Simulate returning user input
    sprintf(output, "You entered: %s", input);
}

int main() {
    char output[100];

    // Five test cases
    handleInput("Hello, World!", output);
    printf("%s\n", output);

    handleInput("C Programming", output);
    printf("%s\n", output);

    handleInput("123456", output);
    printf("%s\n", output);

    handleInput("Secure Code", output);
    printf("%s\n", output);

    handleInput("Test Input", output);
    printf("%s\n", output);

    return 0;
}