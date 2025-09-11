
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* longestDupSubstring(const char* s) {
    if (s == NULL || strlen(s) < 2) {
        return "";
    }
    
    int len = strlen(s);
    char* result = (char*)malloc(len + 1);
    result[0] = '\\0';
    
    for (int sublen = len - 1; sublen > 0; sublen--) {
        for (int i = 0; i + sublen <= len; i++) {
            char* substr = (char*)malloc(sublen + 1);
            strncpy(substr, s + i, sublen);
            substr[sublen] = '\\0';
            
            // Check if substring exists in remaining string
            for (int j = i + 1; j <= len - sublen; j++) {
                if (strncmp(s + j, substr, sublen) == 0) {
                    strcpy(result, substr);
                    free(substr);
                    return result;
                }
            }
            free(substr);
        }
    }
    return result;
}

int main() {
    // Test cases
    printf("%s\\n", longestDupSubstring("banana")); // Expected: "ana"
    printf("%s\\n", longestDupSubstring("abcd"));   // Expected: ""
    printf("%s\\n", longestDupSubstring("aaa"));    // Expected: "aa"
    printf("%s\\n", longestDupSubstring("aaaa"));   // Expected: "aaa"
    printf("%s\\n", longestDupSubstring("ababa"));  // Expected: "aba"
    return 0;
}
