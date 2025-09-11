#include <stdio.h>
#include <string.h>

char* shortestPalindrome(char* s) {
    int len = strlen(s);
    if (len <= 1) {
        return s;
    }
    char rev[len + 1];
    strcpy(rev, s);
    for (int i = 0; i < len / 2; i++) {
        char temp = rev[i];
        rev[i] = rev[len - i - 1];
        rev[len - i - 1] = temp;
    }
    char combined[2 * len + 2];
    snprintf(combined, sizeof(combined), "%s#%s", s, rev);
    int lps[2 * len + 1];
    memset(lps, 0, sizeof(lps));
    int length = 0;
    for (int i = 1; i < strlen(combined); ) {
        if (combined[i] == combined[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    int lengthOfPalindrome = lps[strlen(combined) - 1];
    int toAddLen = len - lengthOfPalindrome;
    char* result = (char*)malloc((toAddLen + len + 1) * sizeof(char));
    strncpy(result, rev, toAddLen);
    strcpy(result + toAddLen, s);
    return result;
}

int main() {
    printf("%s\n", shortestPalindrome("aacecaaa")); // "aaacecaaa"
    printf("%s\n", shortestPalindrome("abcd")); // "dcbabcd"
    printf("%s\n", shortestPalindrome("racecar")); // "racecar"
    printf("%s\n", shortestPalindrome("a")); // "a"
    printf("%s\n", shortestPalindrome("")); // ""
    return 0;
}