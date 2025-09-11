#include <stdio.h>
#include <string.h>

void reverseString(const char* input, char* output) {
    size_t len = strlen(input);
    for (size_t i = 0; i < len; i++) {
        output[i] = input[len - i - 1];
    }
    output[len] = '\0';
}

int main() {
    // Test cases
    char output[100];
    reverseString("hello", output);
    printf("%s\n", output);  // olleh

    reverseString("world", output);
    printf("%s\n", output);  // dlrow

    reverseString("java", output);
    printf("%s\n", output);  // avaj

    reverseString("python", output);
    printf("%s\n", output);  // nohtyp

    reverseString("cpp", output);
    printf("%s\n", output);  // ppc

    return 0;
}