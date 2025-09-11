#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* shortestPalindrome(char* s) {
    int n = strlen(s);
    int i = 0;
    for (int j = n - 1; j >= 0; j--) {
        if (s[i] == s[j]) {
            i++;
        }
    }
    if (i == n) {
        return s;
    }
    char* remaining = (char*)malloc(sizeof(char) * (n - i + 1));
    strncpy(remaining, s + i, n - i);
    remaining[n - i] = '\0';

    // Reverse remaining
    for (int j = 0; j < (n - i) / 2; j++) {
        char temp = remaining[j];
        remaining[j] = remaining[n - i - 1 - j];
        remaining[n - i - 1 - j] = temp;
    }

    char* prefix = shortestPalindrome(strndup(s, i));
    char* result = (char*)malloc(sizeof(char) * (strlen(remaining) + strlen(prefix) + strlen(remaining) + 1));
    strcpy(result, remaining);
    strcat(result, prefix);
    strcat(result, remaining);
    
    free(remaining);
    if (prefix != strndup(s,i)) free(prefix);


    return result;
}

int main() {
    char s1[] = "aacecaaa";
    char* result1 = shortestPalindrome(s1);
    printf("%s\n", result1); // aaacecaaa
    free(result1);

    char s2[] = "abcd";
    char* result2 = shortestPalindrome(s2);
    printf("%s\n", result2); // dcbabcd
    free(result2);
    
    char s3[] = "racecar";
    char* result3 = shortestPalindrome(s3);
    printf("%s\n", result3); // racecar
    free(result3);

    char s4[] = "abb";
    char* result4 = shortestPalindrome(s4);
    printf("%s\n", result4); // bbabb
    free(result4);

    char s5[] = "";
    char* result5 = shortestPalindrome(s5);
    printf("%s\n", result5); // 
    if (result5 != s5) free(result5);

    return 0;
}