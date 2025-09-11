#include <stdio.h>
#include <string.h>

void sanitizeInput(char *input) {
    for (int i = 0; i < strlen(input); ++i) {
        if (input[i] == '<') {
            input[i] = '[';
        } else if (input[i] == '>') {
            input[i] = ']';
        }
    }
}

int main() {
    char testInputs[5][50] = {"Hello", "<script>alert(1)</script>", "<b>Bold</b>", "1234", "<test>"};
    for (int i = 0; i < 5; ++i) {
        sanitizeInput(testInputs[i]);
        printf("Sanitized: %s\n", testInputs[i]);
    }
    return 0;
}