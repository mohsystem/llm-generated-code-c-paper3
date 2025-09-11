#include <stdio.h>
#include <string.h>

char* shortestPalindrome(const char* s) {
    static char buffer[100000]; // sufficient for given constraints
    int n = strlen(s);
    int j = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == s[j]) {
            j++;
        }
    }
    if (j == n) return (char *)s;
    const char *suffix = s + j;
    int suffix_len = n - j;
    for (int k = 0; k < suffix_len; k++) {
        buffer[k] = suffix[suffix_len - k - 1];
    }
    buffer[suffix_len] = '\0';
    strcat(buffer, shortestPalindrome(s));
    strcat(buffer, suffix);
    return buffer;
}

int main() {
    printf("%s\n", shortestPalindrome("aacecaaa")); // aaacecaaa
    printf("%s\n", shortestPalindrome("abcd"));     // dcbabcd
    printf("%s\n", shortestPalindrome("abcba"));    // abcba
    printf("%s\n", shortestPalindrome("race"));     // ecarrace
    printf("%s\n", shortestPalindrome(""));         // ""
    return 0;
}