
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool isPangram(const char* str) {
    bool mark[26] = {false};
    
    for(int i = 0; str[i]; i++) {
        if(isalpha(str[i])) {
            mark[tolower(str[i]) - 'a'] = true;
        }
    }
    
    for(int i = 0; i < 26; i++) {
        if(!mark[i]) return false;
    }
    return true;
}

int main() {
    const char* testCases[] = {
        "The quick brown fox jumps over the lazy dog",
        "Pack my box with five dozen liquor jugs",
        "This is not a pangram",
        "abcdefghijklmnopqrstuvwxyz",
        "The five boxing wizards jump quickly"
    };
    
    for(int i = 0; i < 5; i++) {
        printf("Input: %s\\n", testCases[i]);
        printf("Is Pangram: %s\\n", isPangram(testCases[i]) ? "true" : "false");
    }
    
    return 0;
}
