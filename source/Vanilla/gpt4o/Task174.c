#include <stdio.h>
#include <string.h>

char* shortestPalindrome(const char* s) {
    int n = strlen(s);
    char rev[n + 1];
    for (int i = 0; i < n; ++i) {
        rev[i] = s[n - i - 1];
    }
    rev[n] = '\0';
    
    char l[2 * n + 2];
    sprintf(l, "%s#%s", s, rev);
    int len = strlen(l);
    int p[len];
    memset(p, 0, sizeof(p));
    
    for (int i = 1; i < len; ++i) {
        int j = p[i - 1];
        while (j > 0 && l[i] != l[j]) {
            j = p[j - 1];
        }
        if (l[i] == l[j]) {
            ++j;
        }
        p[i] = j;
    }
    
    int addLen = n - p[len - 1];
    char* result = (char*)malloc((addLen + n + 1) * sizeof(char));
    strncpy(result, rev, addLen);
    strcpy(result + addLen, s);
    
    return result;
}

int main() {
    printf("%s\n", shortestPalindrome("aacecaaa")); // "aaacecaaa"
    printf("%s\n", shortestPalindrome("abcd")); // "dcbabcd"
    printf("%s\n", shortestPalindrome("racecar")); // "racecar"
    printf("%s\n", shortestPalindrome("")); // ""
    printf("%s\n", shortestPalindrome("a")); // "a"
    return 0;
}