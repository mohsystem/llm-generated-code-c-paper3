#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

bool checkPangram(const char* s) {
    bool present[26] = {false};
    while (*s != '\0') {
        if (isalpha(*s)) {
            present[tolower(*s) - 'a'] = true;
        }
        s++;
    }
    for (int i = 0; i < 26; i++) {
        if (!present[i]) return false;
    }
    return true;
}

int main() {
    const char* testCases[] = {
        "The quick brown fox jumps over the lazy dog",
        "Hello, World!",
        "Pack my box with five dozen liquor jugs.",
        "How vexingly quick witted zebras jump!",
        "The five boxing wizards jump quickly."
    };
    for (int i = 0; i < 5; i++) {
        printf("%s\n", checkPangram(testCases[i]) ? "true" : "false");
    }
    return 0;
}