#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool isPangram(const char* input) {
    bool alphabet[26] = {false};
    while (*input) {
        if (isalpha(*input)) {
            alphabet[tolower(*input) - 'a'] = true;
        }
        input++;
    }
    for (int i = 0; i < 26; i++) {
        if (!alphabet[i]) return false;
    }
    return true;
}

int main() {
    const char* testCases[] = {
        "The quick brown fox jumps over the lazy dog",
        "Hello, World!",
        "Pack my box with five dozen liquor jugs.",
        "How vexingly quick daft zebras jump!",
        "The five boxing wizards jump quickly."
    };

    for (int i = 0; i < 5; i++) {
        printf("%s: %s\n", testCases[i], isPangram(testCases[i]) ? "true" : "false");
    }
    return 0;
}