#include <stdio.h>
#include <string.h>

void copyString(const char *input, char *output) {
    strcpy(output, input);
}

void concatenateStrings(const char *str1, const char *str2, char *output) {
    strcpy(output, str1);
    strcat(output, str2);
}

void reverseString(const char *input, char *output) {
    int len = strlen(input);
    for (int i = 0; i < len; i++) {
        output[i] = input[len - i - 1];
    }
    output[len] = '\0';
}

int main() {
    char output[100];

    // Test cases
    copyString("Hello", output);
    printf("%s\n", output); // Output: Hello

    concatenateStrings("Hello", " World", output);
    printf("%s\n", output); // Output: Hello World

    reverseString("Hello", output);
    printf("%s\n", output); // Output: olleH

    copyString("C", output);
    printf("%s\n", output); // Output: C

    concatenateStrings("C", " Program", output);
    printf("%s\n", output); // Output: C Program

    return 0;
}