#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* accum(const char *s) {
    size_t len = strlen(s);
    char* result = (char*)malloc(len * (len + 1) / 2 + len); // Allocate sufficient memory
    if (result == NULL) {
        return NULL; // Handle memory allocation failure
    }
    size_t current_index = 0;
    for (size_t i = 0; i < len; i++) {
        result[current_index++] = toupper(s[i]);
        for (size_t j = 0; j < i; j++) {
            result[current_index++] = tolower(s[i]);
        }
        if (i < len - 1) {
            result[current_index++] = '-';
        }
    }
    result[current_index] = '\0'; // Null-terminate the string
    return result;
}


int main() {
    char* result1 = accum("abcd");
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1); // Free allocated memory
    }
    char* result2 = accum("RqaEzty");
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }
    char* result3 = accum("cwAt");
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }
    char* result4 = accum("ZpglnRWvg");
    if (result4 != NULL) {
        printf("%s\n", result4);
        free(result4);
    }
    char* result5 = accum("NyffsGeyylB");
    if (result5 != NULL) {
        printf("%s\n", result5);
        free(result5);
    }
    return 0;

}