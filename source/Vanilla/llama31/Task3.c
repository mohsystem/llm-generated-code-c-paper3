#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

bool checkPangram(const char* s) {
    bool is_true[26] = {false};
    for (int i = 0; i < strlen(s); i++) {
        if (isalpha(s[i])) {
            is_true[tolower(s[i]) - 'a'] = true;
        }
    }
    for (int i = 0; i < 26; i++) {
        if (!is_true[i]) return false;
    }
    return true;
}

int main() {
    const char* testCases[] = {
        "The quick brown fox jumps over the lazy dog",
        "Abcdefghijklmnopqrstuvwxyz",
        "Pack my box with five dozen liquor jugs",
        "Hello, World!",
        "abcdefghijklmnopqrstuvwxyz"
    };
    for (int i = 0; i < 5; i++) {
        printf("%d\n", checkPangram(testCases[i]));
    }
    return 0;
}