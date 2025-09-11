#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void sortString(char* str) {
    int n = strlen(str);
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (str[i] > str[j]) {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

void longest(const char* s1, const char* s2, char* result) {
    bool seen[26] = {false};
    int k = 0;
    
    while (*s1) {
        if (!seen[*s1 - 'a']) {
            seen[*s1 - 'a'] = true;
            result[k++] = *s1;
        }
        s1++;
    }
    
    while (*s2) {
        if (!seen[*s2 - 'a']) {
            seen[*s2 - 'a'] = true;
            result[k++] = *s2;
        }
        s2++;
    }
    
    result[k] = '\0';
    sortString(result);
}

int main() {
    char result[27];
    
    longest("xyaabbbccccdefww", "xxxxyyyyabklmopq", result);
    printf("%s\n", result);
    
    longest("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz", result);
    printf("%s\n", result);
    
    longest("abc", "def", result);
    printf("%s\n", result);
    
    longest("pqr", "stu", result);
    printf("%s\n", result);
    
    longest("mno", "nop", result);
    printf("%s\n", result);
    
    return 0;
}