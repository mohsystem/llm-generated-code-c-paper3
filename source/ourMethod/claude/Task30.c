
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* longest(const char* s1, const char* s2) {
    // Use array to track unique chars
    int chars[26] = {0};
    
    // Mark chars from first string
    for (int i = 0; s1[i]; i++) {
        chars[s1[i] - 'a'] = 1;
    }
    
    // Mark chars from second string 
    for (int i = 0; s2[i]; i++) {
        chars[s2[i] - 'a'] = 1;
    }
    
    // Allocate result string
    char* result = (char*)malloc(27);
    int pos = 0;
    
    // Build result from marked chars
    for (int i = 0; i < 26; i++) {
        if (chars[i]) {
            result[pos++] = i + 'a';
        }
    }
    result[pos] = '\\0';
    
    return result;
}

int main() {
    // Test cases
    printf("%s\\n", longest("xyaabbbccccdefww", "xxxxyyyyabklmopq")); // "abcdefklmopqwxy"
    printf("%s\\n", longest("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz")); // "abcdefghijklmnopqrstuvwxyz"
    printf("%s\\n", longest("aretheyhere", "yestheyarehere")); // "aehrsty"
    printf("%s\\n", longest("loopingisfunbutdangerous", "lessdangerousthancoding")); // "abcdefghilnoprstu"
    printf("%s\\n", longest("inmanylanguages", "theresapairoffunctions")); // "acefghilmnoprstuy"
    
    return 0;
}
