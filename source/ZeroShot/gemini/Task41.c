#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* processString(const char* input) {
    if (input == NULL) {
        return NULL;
    }
    size_t len = strlen(input);
    char* result = (char*)malloc((len + 1) * sizeof(char)); 
    if (result == NULL) {
        return NULL; // Handle memory allocation failure
    }
    for (size_t i = 0; i < len; i++) {
        result[i] = toupper(input[i]);
    }
    result[len] = '\0';
    return result;
}

int main() {
    char* result1 = processString("hello");
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    char* result2 = processString("world");
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }


    char* result3 = processString("C");
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }

    char* result4 = processString("secure");
    if (result4 != NULL) {
        printf("%s\n", result4);
        free(result4);
    }


    char* result5 = processString(NULL);
    if (result5 == NULL) {
      printf("Received NULL as expected\n");
    }

    return 0;
}