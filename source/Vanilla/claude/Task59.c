
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* accum(const char* s) {
    int len = strlen(s);
    // Calculate required size for result string
    int resultSize = len * (len + 1) / 2 + len;
    char* result = (char*)malloc(resultSize + 1);
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
    result[pos] = '\\0';
    return result;
}

int main() {
    printf("%s\\n", accum("abcd"));
    printf("%s\\n", accum("RqaEzty"));
    printf("%s\\n", accum("cwAt"));
    printf("%s\\n", accum("ZpglnRxqen"));
    printf("%s\\n", accum("NyffsGeyylB"));
    return 0;
}
