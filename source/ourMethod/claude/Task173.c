
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* longestDupSubstring(const char* s) {
    if (s == NULL || strlen(s) < 2) {
        return strdup("");
    }
    
    int n = strlen(s);
    char* result = strdup("");
    char* temp = (char*)malloc((n + 1) * sizeof(char));
    
    // For each possible length of substring
    for (int len = 1; len < n; len++) {
        // For each starting position
        for (int i = 0; i <= n - len; i++) {
            // Extract substring
            strncpy(temp, s + i, len);
            temp[len] = '\\0';
            
            // Check if this substring appears again in remaining string
            char* found = strstr(s + i + 1, temp);
            if (found != NULL) {
                if (strlen(temp) > strlen(result)) {
                    free(result);
                    result = strdup(temp);
                }
            }
        }
    }
    
    free(temp);
    return result;
}

int main() {
    // Test cases
    char* result;
    
    result = longestDupSubstring("banana");
    printf("%s\\n", result); // Expected: "ana"
    free(result);
    
    result = longestDupSubstring("abcd");
    printf("%s\\n", result); // Expected: ""
    free(result);
    
    result = longestDupSubstring("aa");
    printf("%s\\n", result); // Expected: "a"
    free(result);
    
    result = longestDupSubstring("aaa");
    printf("%s\\n", result); // Expected: "aa"
    free(result);
    
    result = longestDupSubstring("aaaaa");
    printf("%s\\n", result); // Expected: "aaaa"
    free(result);
    
    return 0;
}
