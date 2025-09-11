#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void longest(char *s1, char *s2, char *result) {
    int set[26] = {0};
    int i;
    for(i = 0; s1[i]; i++) set[s1[i] - 'a'] = 1;
    for(i = 0; s2[i]; i++) set[s2[i] - 'a'] = 1;
    int j = 0;
    for(i = 0; i < 26; i++) if(set[i]) result[j++] = i + 'a';
    result[j] = '\0';
    qsort(result, j, sizeof(char), strcmp);
}

int main() {
    char result[26];
    longest("xyaabbbccccdefww", "xxxxyyyyabklmopq", result);
    printf("%s\n", result); // "abcdefklmopqwxy"
    longest("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz", result);
    printf("%s\n", result); // "abcdefghijklmnopqrstuvwxyz"
    return 0;
}