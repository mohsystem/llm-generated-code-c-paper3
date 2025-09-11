#include <stdio.h>
#include <string.h>
#include <ctype.h>

void accum(const char *s, char *result) {
    int len = strlen(s);
    int pos = 0;
    for (int i = 0; i < len; i++) {
        result[pos++] = toupper(s[i]);
        for (int j = 0; j < i; j++) {
            result[pos++] = tolower(s[i]);
        }
        if (i < len - 1) {
            result[pos++] = '-';
        }
    }
    result[pos] = '\0';
}

int main() {
    char result[100];
    
    accum("abcd", result);
    printf("%s\n", result); // A-Bb-Ccc-Dddd
    
    accum("RqaEzty", result);
    printf("%s\n", result); // R-Qq-Aaa-Eeee-Zzzzz-Tttttt-Yyyyyyy
    
    accum("cwAt", result);
    printf("%s\n", result); // C-Ww-Aaa-Tttt
    
    accum("Z", result);
    printf("%s\n", result); // Z
    
    accum("aA", result);
    printf("%s\n", result); // A-Aa

    return 0;
}