#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* shortestPalindrome(char* s) {
    if (s == NULL || strlen(s) <= 1) return s;
    int len = strlen(s);
    char* new_s = (char*)malloc((len * 2 + 2) * sizeof(char));
    strcpy(new_s, s);
    strcat(new_s, "#");
    strcat(new_s, s);
    for (int i = len - 1; i >= 0; i--) {
        new_s[len + 1 + i] = s[len - 1 - i];
    }
    int* position = (int*)malloc((len * 2 + 2) * sizeof(int));
    position[0] = 0;
    for (int i = 1; i < len * 2 + 2; i++) {
        int pre_pos = position[i - 1];
        while (pre_pos > 0 && new_s[pre_pos] != new_s[i]) {
            pre_pos = position[pre_pos - 1];
        }
        position[i] = pre_pos + (new_s[pre_pos] == new_s[i] ? 1 : 0);
    }
    int pos = position[len * 2 + 1];
    char* result = (char*)malloc((len * 2 - pos + 1) * sizeof(char));
    for (int i = pos; i < len; i++) {
        result[i - pos] = s[i];
    }
    result[len - pos] = '\0';
    char* reversed = (char*)malloc((len - pos) * sizeof(char));
    for (int i = 0; i < len - pos; i++) {
        reversed[i] = result[len - pos - 1 - i];
    }
    reversed[len - pos] = '\0';
    strcat(reversed, s);
    free(result);
    free(new_s);
    free(position);
    return reversed;
}

int main() {
    char s1[] = "aacecaaa";
    char s2[] = "abcd";
    char s3[] = "abc";
    char s4[] = "abccba";
    char s5[] = "a";

    printf("%s\n", shortestPalindrome(s1)); // "aaacecaaa"
    printf("%s\n", shortestPalindrome(s2)); // "dcbabcd"
    printf("%s\n", shortestPalindrome(s3)); // "cbaabc"
    printf("%s\n", shortestPalindrome(s4)); // "abccba"
    printf("%s\n", shortestPalindrome(s5)); // "a"

    return 0;
}