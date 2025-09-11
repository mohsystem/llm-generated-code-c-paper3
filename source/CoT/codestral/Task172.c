#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int repeatedSubstringPattern(char* text) {
    int len = strlen(text);
    for (int i = 1; i <= len / 2; i++) {
        if (len % i == 0) {
            char* sub = (char*)malloc(sizeof(char) * (i + 1));
            strncpy(sub, text, i);
            sub[i] = '\0';
            int times = len / i;
            char* sb = (char*)malloc(sizeof(char) * (len + 1));
            memset(sb, 0, sizeof(char) * (len + 1));
            for (int j = 0; j < times; j++) {
                strcat(sb, sub);
            }
            if (strcmp(sb, text) == 0) {
                int* distinctSubstrings = (int*)calloc(26, sizeof(int));
                for (int j = 0; j < len - i + 1; j++) {
                    char* substring = (char*)malloc(sizeof(char) * (i + 1));
                    strncpy(substring, text + j, i);
                    substring[i] = '\0';
                    int index = substring[0] - 'a';
                    distinctSubstrings[index] = 1;
                    free(substring);
                }
                int count = 0;
                for (int j = 0; j < 26; j++) {
                    if (distinctSubstrings[j] == 1) {
                        count++;
                    }
                }
                free(distinctSubstrings);
                free(sub);
                free(sb);
                return count;
            }
            free(sub);
            free(sb);
        }
    }
    return 0;
}

int main() {
    printf("%d\n", repeatedSubstringPattern("abcabcabc")); // Output: 3
    printf("%d\n", repeatedSubstringPattern("leetcodeleetcode")); // Output: 2
    return 0;
}