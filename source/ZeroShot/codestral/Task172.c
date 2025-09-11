#include <stdio.h>
#include <string.h>

int repeatedSubstringPattern(char* s) {
    int count = 0;
    int n = strlen(s);
    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0) {
            char substring[i + 1];
            strncpy(substring, s, i);
            substring[i] = '\0';
            char concatenated[n + 1];
            concatenated[0] = '\0';
            for (int j = 0; j < n / i; j++) {
                strcat(concatenated, substring);
            }
            if (strcmp(concatenated, s) == 0) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    printf("%d\n", repeatedSubstringPattern("abcabcabc")); // Output: 3
    printf("%d\n", repeatedSubstringPattern("leetcodeleetcode")); // Output: 2
    printf("%d\n", repeatedSubstringPattern("aaaaa")); // Output: 4
    printf("%d\n", repeatedSubstringPattern("abc")); // Output: 0
    printf("%d\n", repeatedSubstringPattern("aabaaba")); // Output: 2
    return 0;
}