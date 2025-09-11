
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool isPangram(const char* str) {
    // Create boolean array for letters
    bool letters[26] = {false};
    
    // Process each character
    for(int i = 0; str[i]; i++) {
        if(isalpha(str[i])) {
            letters[tolower(str[i]) - 'a'] = true;
        }
    }
    
    // Check if all letters are present
    for(int i = 0; i < 26; i++) {
        if(!letters[i]) return false;
    }
    return true;
}

int main() {
    // Test cases
    const char* tests[] = {
        "The quick brown fox jumps over the lazy dog",
        "Pack my box with five dozen liquor jugs",
        "This is not a pangram",
        "abcdefghijklmnopqrstuvwxyz",
        "The Five boxing wizards jump quickly"
    };
    
    for(int i = 0; i < 5; i++) {
        printf("Input: %s\\n", tests[i]);
        printf("Is Pangram: %s\\n", isPangram(tests[i]) ? "true" : "false");
    }
    
    return 0;
}
