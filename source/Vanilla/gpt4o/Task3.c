#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

bool isPangram(const char *sentence) {
    bool alphabet[26] = { false };
    int index;
    for (int i = 0; sentence[i] != '\0'; i++) {
        if (isalpha(sentence[i])) {
            index = tolower(sentence[i]) - 'a';
            alphabet[index] = true;
        }
    }
    for (int i = 0; i < 26; i++) {
        if (!alphabet[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    printf("%s\n", isPangram("The quick brown fox jumps over the lazy dog") ? "true" : "false"); // true
    printf("%s\n", isPangram("The quick brown fox jumps over the lazy") ? "true" : "false"); // false
    printf("%s\n", isPangram("Pack my box with five dozen liquor jugs") ? "true" : "false"); // true
    printf("%s\n", isPangram("Sphinx of black quartz, judge my vow") ? "true" : "false"); // true
    printf("%s\n", isPangram("Hello, World!") ? "true" : "false"); // false
    return 0;
}