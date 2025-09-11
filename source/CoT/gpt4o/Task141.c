#include <stdio.h>
#include <string.h>

void reverseString(const char* input, char* output) {
    if (input == NULL) {
        output = NULL;
        return;
    }
    int len = strlen(input);
    for (int i = 0; i < len; i++) {
        output[i] = input[len - 1 - i];
    }
    output[len] = '\0';
}

int main() {
    char result[100];

    reverseString("hello", result);
    printf("%s\n", result); // "olleh"

    reverseString("world", result);
    printf("%s\n", result); // "dlrow"

    reverseString("java", result);
    printf("%s\n", result); // "avaj"

    reverseString("python", result);
    printf("%s\n", result); // "nohtyp"

    reverseString("c++", result);
    printf("%s\n", result); // "++c"

    return 0;
}