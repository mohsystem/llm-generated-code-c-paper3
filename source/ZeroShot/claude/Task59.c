
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* accum(const char* s) {
    size_t len = strlen(s);
    size_t result_size = len * (len + 1) / 2 + len;  // Calculate required size
    char* result = (char*)malloc(result_size + 1);
    
    int pos = 0;
    for(size_t i = 0; i < len; i++) {
        if(i > 0) {
            result[pos++] = '-';
        }
        result[pos++] = toupper(s[i]);
        for(size_t j = 0; j < i; j++) {
            result[pos++] = tolower(s[i]);
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
