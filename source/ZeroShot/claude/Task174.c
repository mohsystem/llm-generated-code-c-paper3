
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* reverseStr(const char* str, int start, int end) {
    int len = end - start;
    char* rev = (char*)malloc((len + 1) * sizeof(char));
    for(int i = 0; i < len; i++) {
        rev[i] = str[end - 1 - i];
    }
    rev[len] = '\\0';
    return rev;
}

char* shortestPalindrome(char* s) {
    if(!s || strlen(s) <= 1) return s;
    
    int sLen = strlen(s);
    char* temp = (char*)malloc((2*sLen + 2) * sizeof(char));
    int* lps = (int*)calloc(2*sLen + 2, sizeof(int));
    
    strcpy(temp, s);
    temp[sLen] = '#';
    char* rev = reverseStr(s, 0, sLen);
    strcat(temp, rev);
    free(rev);
    
    // Build LPS array
    for(int i = 1; i < strlen(temp); i++) {
        int len = lps[i-1];
        while(len > 0 && temp[len] != temp[i]) {
            len = lps[len-1];
        }
        if(temp[len] == temp[i]) {
            len++;
        }
        lps[i] = len;
    }
    
    int addLen = sLen - lps[strlen(temp)-1];
    char* result = (char*)malloc((sLen + addLen + 1) * sizeof(char));
    char* add = reverseStr(s, lps[strlen(temp)-1], sLen);
    
    strcpy(result, add);
    strcat(result, s);
    
    free(add);
    free(temp);
    free(lps);
    
    return result;
}

int main() {
    // Test cases
    printf("%s\\n", shortestPalindrome("aacecaaa")); // aaacecaaa
    printf("%s\\n", shortestPalindrome("abcd")); // dcbabcd
    printf("%s\\n", shortestPalindrome("")); // ""
    printf("%s\\n", shortestPalindrome("a")); // a
    printf("%s\\n", shortestPalindrome("aba")); // aba
    return 0;
}
