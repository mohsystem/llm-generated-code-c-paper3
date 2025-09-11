#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool isPangram(const char* input) {
    bool alphabet[26] = {false};
    for (size_t i = 0; i < strlen(input); i++) {
        if (isalpha(input[i])) {
            alphabet[tolower(input[i]) - 'a'] = true;
        }
    }

    for (size_t i = 0; i < 26; i++) {
        if (!alphabet[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    printf("%s\n", isPangram("The quick brown fox jumps over the lazy dog") ? "true" : "false"); // true
    printf("%s\n", isPangram("Hello, World!") ? "true" : "false"); // false
    printf("%s\n", isPangram("ABCDEFGHIJKLMNOPQRSTUVWXYZ") ? "true" : "false"); // true
    printf("%s\n", isPangram("1234567890") ? "true" : "false"); // false
    printf("%s\n", isPangram("The5 quick brown fox jumps over the lazy dog") ? "true" : "false"); // true
    return 0;
}