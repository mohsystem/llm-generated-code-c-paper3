
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* expanded_form(long num) {
    char num_str[20];
    sprintf(num_str, "%ld", num);
    int len = strlen(num_str);
    
    // Allocate memory for result (estimate max size needed)
    char* result = (char*)malloc(100);
    if(result == NULL) return NULL;
    result[0] = '\\0';
    
    int pos = 0;
    for(int i = 0; i < len; i++) {
        if(num_str[i] != '0') {
            if(pos > 0) {
                pos += sprintf(result + pos, " + ");
            }
            pos += sprintf(result + pos, "%c", num_str[i]);
            for(int j = 0; j < len-1-i; j++) {
                pos += sprintf(result + pos, "0");
            }
        }
    }
    
    return result;
}

int main() {
    char* result;
    
    result = expanded_form(12);
    printf("%s\\n", result);    // "10 + 2"
    free(result);
    
    result = expanded_form(42);
    printf("%s\\n", result);    // "40 + 2"
    free(result);
    
    result = expanded_form(70304);
    printf("%s\\n", result);    // "70000 + 300 + 4"
    free(result);
    
    result = expanded_form(4982);
    printf("%s\\n", result);    // "4000 + 900 + 80 + 2"
    free(result);
    
    result = expanded_form(1000);
    printf("%s\\n", result);    // "1000"
    free(result);
    
    return 0;
}
