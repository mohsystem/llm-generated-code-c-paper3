#include <stdio.h>
#include <string.h>

void reverseString(const char *input, char *output) {
    if (input == NULL || output == NULL) return;
    int len = strlen(input);
    for (int i = 0; i < len; i++) {
        output[i] = input[len - i - 1];
    }
    output[len] = '\0';
}

int main() {
    char output[100];
    reverseString("hello", output);
    printf("%s\n", output); // olleh
    reverseString("world", output);
    printf("%s\n", output); // dlrow
    reverseString("C", output);
    printf("%s\n", output); // C
    reverseString("Task141", output);
    printf("%s\n", output); // 141ksaT
    reverseString("", output);
    printf("%s\n", output); // (empty string)
    return 0;
}