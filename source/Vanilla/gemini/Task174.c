#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* shortestPalindrome(char* s) {
    int n = strlen(s);
    char* rev = (char*)malloc(sizeof(char) * (n + 1));
    strcpy(rev, s);
    for (int i = 0, j = n - 1; i < j; i++, j--) {
        char temp = rev[i];
        rev[i] = rev[j];
        rev[j] = temp;
    }
    char* l = (char*)malloc(sizeof(char) * (2 * n + 2));
    strcpy(l, s);
    strcat(l, "#");
    strcat(l, rev);
    int ln = strlen(l);
    int* p = (int*)malloc(sizeof(int) * ln);
    for (int i = 0; i < ln; i++) {
        p[i] = 0;
    }
    for (int i = 1; i < ln; i++) {
        int j = p[i - 1];
        while (j > 0 && l[i] != l[j]) {
            j = p[j - 1];
        }
        if (l[i] == l[j]) {
            j++;
        }
        p[i] = j;
    }

    char* result = (char*)malloc(sizeof(char) * (n + n - p[ln - 1] + 1));
    strncpy(result, rev, n - p[ln - 1]);
    result[n - p[ln - 1]] = '\0';
    strcat(result, s);


    free(rev);
    free(l);
    free(p);
    return result;
}

int main() {
    char s1[] = "aacecaaa";
    char* result1 = shortestPalindrome(s1);
    printf("%s\n", result1); // Output: aaacecaaa
    free(result1);

    char s2[] = "abcd";
    char* result2 = shortestPalindrome(s2);
    printf("%s\n", result2); // Output: dcbabcd
    free(result2);

    char s3[] = "abb";
    char* result3 = shortestPalindrome(s3);
    printf("%s\n", result3); // Output: bbabb
    free(result3);

    char s4[] = "";
    char* result4 = shortestPalindrome(s4);
    printf("%s\n", result4); // Output: ""
    free(result4);

    char s5[] = "a";
    char *result5 = shortestPalindrome(s5);
    printf("%s\n", result5); // Output: a
    free(result5);

    return 0;
}