#include <stdio.h>
#include <string.h>
#include <ctype.h>

void accum(const char* s, char* result) {
    int index = 0;
    for (int i = 0; s[i] != '\0'; ++i) {
        if (i > 0) {
            result[index++] = '-';
        }
        result[index++] = toupper(s[i]);
        for (int j = 0; j < i; ++j) {
            result[index++] = tolower(s[i]);
        }
    }
    result[index] = '\0';
}

int main() {
    char result[100];
    
    accum("abcd", result);
    printf("%s\n", result);      // "A-Bb-Ccc-Dddd"
    
    accum("RqaEzty", result);
    printf("%s\n", result);   // "R-Qq-Aaa-Eeee-Zzzzz-Tttttt-Yyyyyyy"
    
    accum("cwAt", result);
    printf("%s\n", result);      // "C-Ww-Aaa-Tttt"
    
    accum("hello", result);
    printf("%s\n", result);     // "H-Ee-Lll-Llll-Ooooo"
    
    accum("java", result);
    printf("%s\n", result);      // "J-Aa-Vvv-Aaaa"
    
    return 0;
}