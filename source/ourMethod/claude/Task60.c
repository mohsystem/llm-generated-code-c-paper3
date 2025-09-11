
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* expanded_form(int num) {
    if (num <= 0) {
        char* result = (char*)malloc(2);
        strcpy(result, "0");
        return result;
    }
    
    // Calculate buffer size needed
    int temp = num;
    int digits = 0;
    while (temp > 0) {
        digits++;
        temp /= 10;
    }
    
    // Allocate memory for worst case scenario
    // Each digit could need: digit + zeros + " + " = digits + 1 + 3 characters
    char* result = (char*)malloc((digits * (digits + 4) + 1) * sizeof(char));
    if (result == NULL) return NULL;
    result[0] = '\\0';
    
    int position = 1;
    int first = 1;
    
    while (num > 0) {
        int digit = num % 10;
        if (digit != 0) {
            char temp[32];
            sprintf(temp, "%d", digit * position);
            
            if (!first) {
                strcat(result, " + ");
            }
            first = 0;
            
            // Insert at beginning
            int len = strlen(temp);
            memmove(result + len, result, strlen(result) + 1);
            memcpy(result, temp, len);
        }
        num /= 10;
        position *= 10;
    }
    
    return result;
}

int main() {
    // Test cases
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
    
    result = expanded_form(1);
    printf("%s\\n", result);    // "1"
    free(result);
    
    return 0;
}
