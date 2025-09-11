#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* concatenateStrings(char** strings, int count) {
    int totalLength = 1; // Start with 1 for null terminator
    for (int i = 0; i < count; i++) {
        totalLength += strlen(strings[i]);
    }

    char* result = (char*)malloc(totalLength * sizeof(char));
    if (result == NULL) {
        return NULL; // Memory allocation failed
    }

    result[0] = '\0'; // Initialize as empty string
    for (int i = 0; i < count; i++) {
        strcat(result, strings[i]);
    }

    return result;
}

int main() {
    char* strings1[] = {"Hello", ", ", "world", "!"};
    char* result1 = concatenateStrings(strings1, 4);
    printf("%s\n", result1);
    free(result1);

    char* strings2[] = {"Java", " ", "is", " ", "fun"};
    char* result2 = concatenateStrings(strings2, 5);
    printf("%s\n", result2);
    free(result2);

    char* strings3[] = {"This", " ", "is", " ", "a", " ", "test"};
    char* result3 = concatenateStrings(strings3, 7);
    printf("%s\n", result3);
    free(result3);

    char* strings4[] = {"Empty", ""};
    char* result4 = concatenateStrings(strings4, 2);
    printf("%s\n", result4);
    free(result4);
    
    char* strings5[] = {"Single"};
    char* result5 = concatenateStrings(strings5, 1);
    printf("%s\n", result5);
    free(result5);


    return 0;
}