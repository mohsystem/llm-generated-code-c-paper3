#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool isPangram(const char *sentence) {
    char alphabet[26] = {0}; // Initialize all elements to 0
    for (int i = 0; i < strlen(sentence); i++) {
        char c = tolower(sentence[i]);
        if (c >= 'a' && c <= 'z') {
            alphabet[c - 'a'] = 1;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (alphabet[i] == 0) {
            return false;
        }
    }

    return true;
}

int main() {
    const char *testCases[] = {
        "The quick brown fox jumps over the lazy dog",
        "This is not a pangram",
        "abcdefghijklmnopqrstuvwxyz",
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()",
        "The five boxing wizards jump quickly."
    };
    bool expectedResults[] = {true, false, true, true, true};

    for (int i = 0; i < 5; i++) {
        bool result = isPangram(testCases[i]);
        printf("Test case %d: \"%s\"\n", i + 1, testCases[i]);
        printf("Expected: %s, Actual: %s\n", expectedResults[i] ? "true" : "false", result ? "true" : "false");
        printf("%s\n\n", (result == expectedResults[i] ? "Pass" : "Fail"));
    }
    return 0;
}