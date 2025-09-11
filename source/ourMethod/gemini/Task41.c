#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Define a maximum input size to prevent buffer overflows
#define MAX_INPUT_SIZE 256


char* processString(const char* input) {
    if (input == NULL) {
        return "";
    }
    size_t len = strlen(input);
    char* processedString = (char*)malloc((len + 1) * sizeof(char)); // Allocate memory
    if (processedString == NULL) {
        return NULL; // Handle memory allocation failure
    }

    for (size_t i = 0; i < len; i++) {
        processedString[i] = toupper(input[i]);
    }
    processedString[len] = '\0'; // Null-terminate
    return processedString;
}

int main() {
    char input[MAX_INPUT_SIZE];
     char* result;

    strcpy(input, "hello");
    result = processString(input);
    printf("%s\n", result);
    free(result);


    strcpy(input, "world");
    result = processString(input);
    printf("%s\n", result);
    free(result);

    strcpy(input, "12345");
    result = processString(input);
    printf("%s\n", result);
    free(result);


    strcpy(input,"");
    result = processString(input);
    printf("%s\n", result);
    free(result);

    result = processString(NULL);
    printf("%s\n", result);
    //free(result); No need to free "" as its not allocated.



    return 0;
}