#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

bool isPangram(const char* input) {
    bool isTrue[26] = {false};
    while (*input) {
        char ch = tolower(*input);
        if (ch >= 'a' && ch <= 'z') {
            isTrue[ch - 'a'] = true;
        }
        input++;
    }
    for (int i = 0; i < 26; i++) {
        if (!isTrue[i]) return false;
    }
    return true;
}

int main() {
    const char* testCases[] = {
        "The quick brown fox jumps over the lazy dog",
        "Hello World",
        "Abcdefghijklmnopqrstuvwxyz",
        "Pack my box with five dozen liquor jugs",
        "How vexingly quick daft zebras jump!"
    };
    for (int i = 0; i < 5; i++) {
        printf("%s: %s\n", testCases[i], isPangram(testCases[i]) ? "true" : "false");
    }
    return 0;
}