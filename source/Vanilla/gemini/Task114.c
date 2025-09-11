#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to reverse a string
char* reverseString(const char *str) {
    int len = strlen(str);
    char *reversed = (char*)malloc(sizeof(char) * (len + 1));
    if (reversed == NULL) {
        return NULL; // Handle memory allocation failure
    }
    for (int i = 0; i < len; i++) {
        reversed[i] = str[len - 1 - i];
    }
    reversed[len] = '\0';
    return reversed;
}


char* stringOperations(const char *str1, const char *str2, const char *operation) {
    if (strcmp(operation, "copy") == 0) {
        char *copy = strdup(str1); // Allocate memory and copy
        return copy; 
    } else if (strcmp(operation, "concatenate") == 0) {
        char *concatenated = (char*)malloc(strlen(str1) + strlen(str2) + 1);
        if (concatenated == NULL) {
            return NULL;
        }
        strcpy(concatenated, str1);
        strcat(concatenated, str2);
        return concatenated;
    } else if (strcmp(operation, "reverse") == 0) {
       return reverseString(str1);
    } else {
        return strdup("Invalid operation"); // Allocate and return a copy
    }
}

int main() {
    char *result;

    result = stringOperations("hello", "world", "copy");
    printf("%s\n", result);
    free(result); // Free allocated memory

    result = stringOperations("hello", "world", "concatenate");
    printf("%s\n", result);
    free(result);

    result = stringOperations("hello", "world", "reverse");
    printf("%s\n", result);
    free(result);

    result = stringOperations("coding", "challenge", "copy");
    printf("%s\n", result);
    free(result);


    result = stringOperations("open", "ai", "concatenate");
    printf("%s\n", result);
    free(result);

    return 0;
}