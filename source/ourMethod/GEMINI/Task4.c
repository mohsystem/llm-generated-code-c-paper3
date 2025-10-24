#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief Checks if a string is an isogram (has no repeating letters, case-insensitive).
 *
 * @param str The string to check. Assumed to contain only letters.
 * @return true if the string is an isogram, false otherwise.
 */
bool isIsogram(const char* str) {
    if (str == NULL) {
        return false; // Treat NULL input as not an isogram.
    }

    // A boolean array is efficient for a fixed, small character set.
    // Initialize all elements to false.
    bool seen[26] = {false};

    for (int i = 0; str[i] != '\0'; ++i) {
        // Safely convert character to its lowercase equivalent.
        // The cast to unsigned char is important to prevent undefined behavior
        // if char is signed and has a negative value.
        int c = tolower((unsigned char)str[i]);
        
        // Assuming input contains only letters as per the prompt.
        // A more robust solution would check if c is a letter.
        if (c >= 'a' && c <= 'z') {
            int index = c - 'a';
            if (seen[index]) {
                return false;
            }
            seen[index] = true;
        }
    }

    return true;
}

int main() {
    // Test cases
    const char* testCases[] = {
        "Dermatoglyphics",
        "aba",
        "moOse",
        "isogram",
        ""
    };
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; ++i) {
        printf("\"%s\" --> %s\n", testCases[i], isIsogram(testCases[i]) ? "true" : "false");
    }

    return 0;
}