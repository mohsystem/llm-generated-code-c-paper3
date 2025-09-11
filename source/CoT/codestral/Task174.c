#include <stdio.h>
#include <string.h>

void reverse(char* str, int len) {
    int start = 0;
    int end = len - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

char* shortestPalindrome(char* s) {
    int len = strlen(s);
    int i = 0;
    for (int j = len - 1; j >= 0; j--) {
        if (s[i] == s[j]) {
            i++;
        }
    }
    if (i == len) {
        return s;
    }
    char suffix[len + 1];
    strncpy(suffix, s + i, len - i);
    suffix[len - i] = '\0';
    reverse(suffix, strlen(suffix));
    char prefix[len + 1];
    strcpy(prefix, suffix);
    strncpy(s + len, shortestPalindrome(s), i);
    strcpy(s + len + i, suffix);
    return s;
}

int main() {
    char s1[100] = "aacecaaa";
    printf("%s\n", shortestPalindrome(s1)); // Output: "aaacecaaa"
    char s2[100] = "abcd";
    printf("%s\n", shortestPalindrome(s2)); // Output: "dcbabcd"
    return 0;
}