#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* accum(char* s) {
    int len = strlen(s);
    char* result = (char*)malloc(sizeof(char) * (len * (len + 1) / 2 + len));
    int current_index = 0;
    for (int i = 0; i < len; i++) {
        result[current_index++] = toupper(s[i]);
        for (int j = 0; j < i; j++) {
            result[current_index++] = tolower(s[i]);
        }
        if (i < len - 1) {
            result[current_index++] = '-';
        }
    }
    result[current_index] = '\0';
    return result;
}

int main() {
    char* result1 = accum("abcd");
    printf("%s\n", result1);
    free(result1);

    char* result2 = accum("RqaEzty");
    printf("%s\n", result2);
    free(result2);
    
    char* result3 = accum("cwAt");
    printf("%s\n", result3);
    free(result3);

    char* result4 = accum("xyz");
    printf("%s\n", result4);
    free(result4);
    
    char* result5 = accum("NyffsGeyylB");
    printf("%s\n", result5);
    free(result5);

    return 0;
}