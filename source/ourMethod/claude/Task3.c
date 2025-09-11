
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool isPangram(const char* str) {
    // Create array to track letter occurrences
    bool letters[26] = {false};
    
    // Process each character
    for(size_t i = 0; str[i] != '\\0'; i++) {
        if(isalpha(str[i])) {
            letters[tolower(str[i]) - 'a'] = true;
        }
    }
    
    // Check if all letters found
    for(int i = 0; i < 26; i++) {
        if(!letters[i]) return false;
    }
    
    return true;
}

int main() {
    // Test cases
    printf("%d\\n", isPangram("The quick brown fox jumps over the lazy dog")); // 1
    printf("%d\\n", isPangram("This is not a pangram")); // 0
    printf("%d\\n", isPangram("Pack my box with five dozen liquor jugs.")); // 1
    printf("%d\\n", isPangram("abcdefghijklmnopqrstuvwxyz")); // 1
    printf("%d\\n", isPangram("A pangram IS a sentence using every letter of the ALPHABET.")); // 1
    
    return 0;
}
