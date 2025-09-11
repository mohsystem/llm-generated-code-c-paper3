
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* shortestPalindrome(const char* s) {
    if (!s || strlen(s) <= 1) {
        char* result = (char*)malloc(strlen(s) + 1);
        strcpy(result, s);
        return result;
    }
    
    // Create temp string s + "#" + reverse(s)
    int len = strlen(s);
    char* temp = (char*)malloc(2 * len + 2);
    int* lps = (int*)calloc(2 * len + 2, sizeof(int));
    
    // Copy s to temp
    strcpy(temp, s);
    temp[len] = '#';
    
    // Add reverse of s
    for (int i = 0; i < len; i++) {
        temp[len + 1 + i] = s[len - 1 - i];
    }
    temp[2 * len + 1] = '\\0';
    
    // Computing KMP pattern
    for (int i = 1; i < 2 * len + 1; i++) {
        int length = lps[i-1];
        while (length > 0 && temp[length] != temp[i]) {
            length = lps[length-1];
        }
        if (temp[length] == temp[i]) {
            length++;
        }
        lps[i] = length;
    }
    
    // Create result
    int add_len = len - lps[2 * len];
    char* result = (char*)malloc(len + add_len + 1);
    
    // Add reversed part
    for (int i = 0; i < add_len; i++) {
        result[i] = s[len - 1 - i];
    }
    
    // Add original string
    strcpy(result + add_len, s);
    
    free(temp);
    free(lps);
    return result;
}

int main() {
    // Test cases
    char* result;
    
    result = shortestPalindrome("aacecaaa");
    printf("%s\\n", result);  // aaacecaaa
    free(result);
    
    result = shortestPalindrome("abcd");
    printf("%s\\n", result);  // dcbabcd
    free(result);
    
    result = shortestPalindrome("");
    printf("%s\\n", result);  // ""
    free(result);
    
    result = shortestPalindrome("a");
    printf("%s\\n", result);  // a
    free(result);
    
    result = shortestPalindrome("aba");
    printf("%s\\n", result);  // aba
    free(result);
    
    return 0;
}
