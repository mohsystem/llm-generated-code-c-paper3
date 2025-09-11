
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* accum(const char* input) {
    if (!input) return NULL;
    
    int len = strlen(input);
    int result_size = len * (len + 1) / 2 + len; // Calculate required size
    char* result = (char*)malloc(result_size + 1);
    if (!result) return NULL;
    
    int pos = 0;
    for (int i = 0; i < len; i++) {
        if (i > 0) result[pos++] = '-';
        result[pos++] = toupper(input[i]);
        for (int j = 0; j < i; j++) {
            result[pos++] = tolower(input[i]);
        }
    }
    result[pos] = '\\0';
    return result;
}

int main() {
    char* result;
    
    result = accum("abcd");
    printf("%s\\n", result);
    free(result);
    
    result = accum("RqaEzty");
    printf("%s\\n", result);
    free(result);
    
    result = accum("cwAt");
    printf("%s\\n", result);
    free(result);
    
    result = accum("ZpglnRxqen");
    printf("%s\\n", result);
    free(result);
    
    result = accum("NyffsGeyylB");
    printf("%s\\n", result);
    free(result);
    
    return 0;
}
