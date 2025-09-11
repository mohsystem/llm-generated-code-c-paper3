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
    // Test cases
    char* test1[] = {"Hello", " ", "world"};
    char* result1 = concatenateStrings(test1, 3);
    printf("%s\n", result1); // Expected: Hello world
    free(result1);

    char* test2[] = {};
    char* result2 = concatenateStrings(test2, 0);
    printf("%s\n", result2); // Expected: ""
    free(result2);

    char* test3[] = {"Java", "Python", "C++", "C"};
    char* result3 = concatenateStrings(test3, 4);
    printf("%s\n", result3); // Expected: JavaPythonC++C
    free(result3);


    char* test4[] = {"Test", "", "case"};
    char* result4 = concatenateStrings(test4, 3);
    printf("%s\n", result4); // Expected: Testcase
    free(result4);

    char* test5[] = {"Multiple", " strings ", "concatenated."};
    char* result5 = concatenateStrings(test5, 3);
    printf("%s\n", result5); // Expected: Multiple strings concatenated.
    free(result5);

    return 0;
}