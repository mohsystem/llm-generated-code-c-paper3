
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* longestDupSubstring(const char* s) {
    if (s == NULL || strlen(s) < 2) {
        return "";
    }
    
    int n = strlen(s);
    char* result = (char*)malloc((n + 1) * sizeof(char));
    result[0] = '\\0';
    
    for (int len = n-1; len > 0; len--) {
        for (int i = 0; i <= n-len; i++) {
            char temp[n + 1];
            strncpy(temp, s + i, len);
            temp[len] = '\\0';
            
            // Check if substring exists in remaining string
            char* found = strstr(s + i + 1, temp);
            if (found != NULL) {
                strcpy(result, temp);
                return result;
            }
        }
    }
    return result;
}

int main() {
    // Test cases
    printf("%s\\n", longestDupSubstring("banana"));      // "ana"
    printf("%s\\n", longestDupSubstring("abcd"));        // ""
    printf("%s\\n", longestDupSubstring("aaaa"));        // "aaa"
    printf("%s\\n", longestDupSubstring("aabaa"));       // "aa"
    printf("%s\\n", longestDupSubstring("mississippi")); // "issi"
    return 0;
}
