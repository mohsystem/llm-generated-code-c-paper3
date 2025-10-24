
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
// Function to check if a string is an isogram
// Returns true if no letter repeats (case-insensitive), false otherwise
bool isIsogram(const char *str) {
    // Input validation: check for NULL pointer
    if (str == NULL) {
        return false;
    }

    // Calculate string length with bounds checking
    size_t len = strlen(str);

    // Empty string is considered an isogram per specification
    if (len == 0) {
        return true;
    }

    // Input validation: check string length to prevent excessive processing
    // Max 26 unique letters in English alphabet
    if (len > 26) {
        return false;
    }

    // Use a fixed-size array to track seen letters (a-z)
    // Initialize to false - no letters seen yet
    bool seen[26];
    memset(seen, 0, sizeof(seen));

    // Iterate through each character with bounds checking
    for (size_t i = 0; i < len; ++i) {
        // Bounds check: ensure we don't read past string end
        if (str[i] == '\0') {
            break;
        }

        unsigned char c = (unsigned char)str[i];

        // Validate that character is a letter (input sanitization)
        if (!isalpha(c)) {
            // Skip non-letter characters as per problem statement
            continue;
        }

        // Convert to lowercase for case-insensitive comparison
        // Cast to unsigned char to avoid undefined behavior with negative values
        unsigned char lower = (unsigned char)tolower(c);

        // Calculate index (0-25) with bounds validation
        int index = (int)(lower - 'a');

        // Bounds check to prevent out-of-range array access
        if (index < 0 || index >= 26) {
            continue; // Skip invalid characters
        }

        // Check if letter was already seen
        if (seen[index]) {
            return false; // Duplicate found, not an isogram
        }

        // Mark letter as seen
        seen[index] = true;
    }

    return true; // No duplicates found
}


int main() {
    // Test cases to verify functionality
    printf("Test 1: \"Dermatoglyphics\" -> %s\n", isIsogram("Dermatoglyphics") ? "true" : "false");
    printf("Test 2: \"aba\" -> %s\n", isIsogram("aba") ? "true" : "false");
    printf("Test 3: \"moOse\" -> %s\n", isIsogram("moOse") ? "true" : "false");
    printf("Test 4: \"\" -> %s\n", isIsogram("") ? "true" : "false");
    printf("Test 5: \"abcdefg\" -> %s\n", isIsogram("abcdefg") ? "true" : "false");
    
    return 0;
}
