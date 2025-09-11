
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char* longest(const char* s1, const char* s2) {
    static char result[27];  // Static to return local array
    bool letters[26] = {false};
    int index = 0;
    
    // Mark all present characters
    for(int i = 0; s1[i]; i++) {
        letters[s1[i] - 'a'] = true;
    }
    for(int i = 0; s2[i]; i++) {
        letters[s2[i] - 'a'] = true;
    }
    
    // Build result string
    for(int i = 0; i < 26; i++) {
        if(letters[i]) {
            result[index++] = i + 'a';
        }
    }
    result[index] = '\\0';
    
    return result;
}

int main() {
    // Test case 1
    printf("%s\\n", longest("xyaabbbccccdefww", "xxxxyyyyabklmopq"));
    
    // Test case 2
    printf("%s\\n", longest("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz"));
    
    // Test case 3
    printf("%s\\n", longest("abc", "def"));
    
    // Test case 4
    printf("%s\\n", longest("aaaa", "bbbb"));
    
    // Test case 5
    printf("%s\\n", longest("", "xyz"));
    
    return 0;
}
