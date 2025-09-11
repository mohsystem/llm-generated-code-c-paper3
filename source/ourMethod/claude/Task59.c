
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* accum(const char* input) {
    if (input == NULL) {
        return strdup("");
    }
    
    size_t len = strlen(input);
    if (len == 0) {
        return strdup("");
    }
    
    // Validate input contains only letters
    for (size_t i = 0; i < len; i++) {
        if (!isalpha((unsigned char)input[i])) {
            return strdup("");
        }
    }
    
    // Calculate required buffer size
    size_t total_size = len; // For first chars
    for (size_t i = 0; i < len; i++) {
        total_size += i;     // For repeated chars
    }
    total_size += len;       // For hyphens
    
    char* result = (char*)malloc(total_size + 1);
    if (result == NULL) {
        return NULL;
    }
    
    size_t pos = 0;
    for (size_t i = 0; i < len; i++) {
        result[pos++] = toupper((unsigned char)input[i]);
        
        for (size_t j = 0; j < i; j++) {
            result[pos++] = tolower((unsigned char)input[i]);
        }
        
        if (i < len - 1) {
            result[pos++] = '-';
        }
    }
    result[pos] = '\\0';
    
    return result;
}

int main() {
    // Test cases
    char* result;
    
    result = accum("abcd");
    printf("%s\\n", result);     // "A-Bb-Ccc-Dddd"
    free(result);
    
    result = accum("RqaEzty");
    printf("%s\\n", result);     // "R-Qq-Aaa-Eeee-Zzzzz-Tttttt-Yyyyyyy"
    free(result);
    
    result = accum("cwAt");
    printf("%s\\n", result);     // "C-Ww-Aaa-Tttt"
    free(result);
    
    result = accum("");
    printf("%s\\n", result);     // ""
    free(result);
    
    result = accum("Z");
    printf("%s\\n", result);     // "Z"
    free(result);
    
    return 0;
}
