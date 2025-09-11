#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* accum(char* s) {
    int len = strlen(s);
    char* result = (char*)malloc(sizeof(char) * (len * (len + 1) / 2 + len)); 
    int index = 0;
    for (int i = 0; i < len; i++) {
        result[index++] = toupper(s[i]);
        for (int j = 0; j < i; j++) {
            result[index++] = tolower(s[i]);
        }
        if (i < len - 1) {
            result[index++] = '-';
        }
    }
    result[index] = '\0';
    return result;
}

int main() {
    char* test1 = accum("abcd");
    printf("%s\n", test1); // Expected: "A-Bb-Ccc-Dddd"
    free(test1);

    char* test2 = accum("RqaEzty");
    printf("%s\n", test2); // Expected: "R-Qq-Aaa-Eeee-Zzzzz-Tttttt-Yyyyyyy"
    free(test2);
    
    char* test3 = accum("cwAt");
    printf("%s\n", test3); // Expected: "C-Ww-Aaa-Tttt"
    free(test3);

    char* test4 = accum("xyz");
    printf("%s\n", test4); // Expected: "X-Yy-Zzz"
    free(test4);

    char* test5 = accum("NyffsGeyylB");
    printf("%s\n", test5); // Expected: "N-Yy-Fff-Ffff-Sssss-Gggggg-Eeeeeee-Yyyyyyyy-Yyyyyyyyy-Llllllllll-Bbbbbbbbbbb"
    free(test5);

    return 0;
}