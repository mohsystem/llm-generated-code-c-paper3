#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/**
 * @brief Checks if a string is a pangram.
 * A pangram is a sentence containing every letter of the English alphabet at least once.
 * The check is case-insensitive and ignores numbers and punctuation.
 *
 * @param s The input C-string to check.
 * @return true if the string is a pangram, false otherwise.
 */
bool isPangram(const char* s) {
    if (s == NULL) {
        return false;
    }

    bool seen[26] = {false};
    int uniqueCount = 0;
    const int ALPHABET_SIZE = 26;

    for (int i = 0; s[i] != '\0'; ++i) {
        // cast to unsigned char is necessary to prevent undefined behavior
        // for negative char values when passed to ctype functions.
        char c = tolower((unsigned char)s[i]);
        if (c >= 'a' && c <= 'z') {
            int index = c - 'a';
            if (!seen[index]) {
                seen[index] = true;
                uniqueCount++;
                if (uniqueCount == ALPHABET_SIZE) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    const char* testCases[] = {
        "The quick brown fox jumps over the lazy dog",
        "This is not a pangram",
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
        "A quick brown fox jumps over the lazy cat",
        ""
    };

    bool expectedResults[] = {
        true,
        false,
        true,
        false,
        false
    };

    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; ++i) {
        bool result = isPangram(testCases[i]);
        printf("Test Case %d: \"%s\"\n", i + 1, testCases[i]);
        printf("Is Pangram: %s\n", result ? "true" : "false");
        printf("Expected: %s\n", expectedResults[i] ? "true" : "false");
        printf("Result matches expected: %s\n", (result == expectedResults[i]) ? "true" : "false");
        printf("\n");
    }

    return 0;
}