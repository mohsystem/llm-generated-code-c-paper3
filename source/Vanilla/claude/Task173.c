
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* longestDupSubstring(char* s) {
    int len = strlen(s);
    char* result = (char*)malloc(len + 1);
    result[0] = '\\0';
    
    for(int i = 0; i < len; i++) {
        for(int j = i + 1; j < len; j++) {
            char* sub = (char*)malloc(len + 1);
            strncpy(sub, s + i, j - i + 1);
            sub[j - i + 1] = '\\0';
            
            char* rest = s + j + 1;
            char* found = strstr(rest, sub);
            
            if(found != NULL && strlen(sub) > strlen(result)) {
                strcpy(result, sub);
            }
            free(sub);
        }
    }
    return result;
}

int main() {
    printf("%s\\n", longestDupSubstring("banana")); // ana
    printf("%s\\n", longestDupSubstring("abcd")); // ""
    printf("%s\\n", longestDupSubstring("aaa")); // aa
    printf("%s\\n", longestDupSubstring("aaaa")); // aaa
    printf("%s\\n", longestDupSubstring("abcabc")); // abc
    return 0;
}
