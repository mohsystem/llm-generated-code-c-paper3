#include <stdio.h>
#include <string.h>

char* handleInput(int bufferSize, const char* input) {
    char* buffer = (char*)malloc(bufferSize * sizeof(char));
    if (buffer == NULL) {
        return NULL; // Handle memory allocation failure
    }
    int index = 0;

    for (int i = 0; input[i] != '\0' && index < bufferSize; i++) {
        buffer[index++] = input[i];
    }
    buffer[index] = '\0'; // Null-terminate the string

    return buffer;
}

int main() {
    char* result1 = handleInput(10, "This is a test input");
    printf("%s\n", result1);
    free(result1); // Free allocated memory


    char* result2 = handleInput(5, "Short");
    printf("%s\n", result2);
    free(result2);

    char* result3 = handleInput(20, "A longer input string");
    printf("%s\n", result3);
    free(result3);

    char* result4 = handleInput(7, "Input with spaces");
    printf("%s\n", result4);
    free(result4);

    char* result5 = handleInput(15, "Special characters like !@#$%^");
    printf("%s\n", result5);
    free(result5);

    return 0;
}