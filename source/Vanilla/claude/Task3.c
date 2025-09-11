
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool isPangram(const char* str) {
    bool mark[26] = {false};
    
    for(int i = 0; str[i]; i++) {
        char c = tolower(str[i]);
        if(c >= 'a' && c <= 'z') {
            mark[c - 'a'] = true;
        }
    }
    
    for(int i = 0; i < 26; i++) {
        if(!mark[i]) return false;
    }
    return true;
}

int main() {
    const char* tests[] = {
        "The quick brown fox jumps over the lazy dog",
        "Pack my box with five dozen liquor jugs",
        "This is not a pangram",
        "abcdefghijklmnopqrstuvwxyz",
        "The five boxing wizards jump quickly"
    };
    
    for(int i = 0; i < 5; i++) {
        printf("Input: %s\\n", tests[i]);
        printf("Is Pangram: %s\\n", isPangram(tests[i]) ? "true" : "false");
    }
    
    return 0;
}
