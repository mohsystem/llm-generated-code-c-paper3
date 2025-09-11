#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenateStrings(char** strings, int numStrings) {
    size_t totalLength = 1; // Start with 1 for null terminator
    for (int i = 0; i < numStrings; i++) {
        totalLength += strlen(strings[i]);
    }

    char* result = (char*)malloc(totalLength * sizeof(char));
    if (result == NULL) {
        return NULL; // Memory allocation failed
    }
    result[0] = '\0'; // Initialize as empty string

    for (int i = 0; i < numStrings; i++) {
        strcat(result, strings[i]);
    }

    return result;
}

int main() {
    int numStrings;
    printf("Enter the number of strings: ");
    scanf("%d", &numStrings);
    getchar(); // Consume newline

    char** strings = (char**)malloc(numStrings * sizeof(char*));


    for (int i = 0; i < numStrings; i++) {
        printf("Enter string %d: ", i + 1);
        char buffer[1024]; // Adjust size as needed
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0; // Remove trailing newline
        strings[i] = strdup(buffer);
    }

    char* concatenatedString = concatenateStrings(strings, numStrings);
    if (concatenatedString != NULL) {
        printf("Concatenated string: %s\n", concatenatedString);
        free(concatenatedString);
    } else {
        printf("Memory allocation failed.\n");
    }


    char* test1[] = {"Hello", ", ", "world", "!"};
    printf("%s\n", concatenateStrings(test1, 4));
    char* test2[] = {"Java", "Python", "C++", "C"};
    printf("%s\n", concatenateStrings(test2, 4));
    char* test3[] = {"", "", ""};
    printf("%s\n", concatenateStrings(test3, 3));
    char* test4[] = {"Single"};
    printf("%s\n", concatenateStrings(test4, 1));
    char* test5[] = {"Test", "1", "Test", "2"};
    printf("%s\n", concatenateStrings(test5, 4));

    // Free allocated memory for input strings
    for (int i = 0; i < numStrings; i++) {
        free(strings[i]);
    }
    free(strings);


    return 0;
}