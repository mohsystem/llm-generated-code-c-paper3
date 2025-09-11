#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* shortestPalindrome(char* s) {
    int n = strlen(s);
    char* reversed_s = (char*)malloc(sizeof(char) * (n + 1));
    for (int i = 0; i < n; i++) {
        reversed_s[i] = s[n - 1 - i];
    }
    reversed_s[n] = '\0';

    char* combined = (char*)malloc(sizeof(char) * (2 * n + 2));
    strcpy(combined, s);
    strcat(combined, "#");
    strcat(combined, reversed_s);

    int combined_len = strlen(combined);
    int* kmp_table = (int*)malloc(sizeof(int) * combined_len);
    for (int i = 0; i < combined_len; i++) {
        kmp_table[i] = 0;
    }

    for (int i = 1; i < combined_len; i++) {
        int j = kmp_table[i - 1];
        while (j > 0 && combined[i] != combined[j]) {
            j = kmp_table[j - 1];
        }
        if (combined[i] == combined[j]) {
            j++;
        }
        kmp_table[i] = j;
    }

    int prefix_len = kmp_table[combined_len - 1];
    char* result = (char*)malloc(sizeof(char) * (n + n - prefix_len+1));
    strncpy(result, reversed_s, n - prefix_len);
    result[n-prefix_len]='\0';
    strcat(result, s);


    free(reversed_s);
    free(combined);
    free(kmp_table);
    return result;
}

int main() {
    char s1[] = "aacecaaa";
    char* result1 = shortestPalindrome(s1);
    printf("%s\n", result1); // Expected: aaacecaaa
    free(result1);

    char s2[] = "abcd";
    char* result2 = shortestPalindrome(s2);
    printf("%s\n", result2); // Expected: dcbabcd
    free(result2);
    
    char s3[] = "racecar";
    char* result3 = shortestPalindrome(s3);
    printf("%s\n", result3); // Expected: racecar
    free(result3);

    char s4[] = "";
    char* result4 = shortestPalindrome(s4);
    printf("%s\n", result4); // Expected: 
    free(result4);

    char s5[] = "a";
    char* result5 = shortestPalindrome(s5);
    printf("%s\n", result5); // Expected: a
    free(result5);

    return 0;
}