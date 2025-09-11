#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* concatenateStrings(char** strings, int numStrings) {
    size_t totalLength = 1; // Start with 1 for null terminator
    for (int i = 0; i < numStrings; i++) {
        totalLength += strlen(strings[i]);
    }

    char* concatenatedString = (char*)malloc(totalLength * sizeof(char));
    if (concatenatedString == NULL) {
        return NULL; // Handle memory allocation failure
    }

    concatenatedString[0] = '\0'; // Initialize as empty string

    for (int i = 0; i < numStrings; i++) {
        strcat(concatenatedString, strings[i]);
    }

    return concatenatedString;
}

int main() {
    char* strings1[] = {"Hello", " ", "World"};
    char* result1 = concatenateStrings(strings1, 3);
    printf("%s\n", result1);
    free(result1);

    char* strings2[] = {"String", "1"};
    char* result2 = concatenateStrings(strings2, 2);
    printf("%s\n", result2);
    free(result2);


    char* strings3[] = {"a", "b", "c"};
    char* result3 = concatenateStrings(strings3, 3);
    printf("%s\n", result3);
    free(result3);

    char* strings4[] = {""};
    char* result4 = concatenateStrings(strings4, 1);
    printf("%s\n", result4);
    free(result4);


    char* strings5[] = {"Test", " ", "case", " ", "5"};
    char* result5 = concatenateStrings(strings5, 5);
    printf("%s\n", result5);
    free(result5);



    return 0;
}