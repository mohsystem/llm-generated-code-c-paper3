#include <stdio.h>
#include <string.h>

char* handleUserInput(int bufferSize) {
    char buffer[bufferSize];
    char input[1024]; //increased input buffer size to prevent potential overflow.

    printf("Enter input: ");
    fgets(input, sizeof(input), stdin);

    // Remove the newline character from fgets if present
    input[strcspn(input, "\n")] = 0;

    if (strlen(input) > bufferSize) {
        return "Input exceeds buffer size.";
    }

    strncpy(buffer, input, strlen(input));
    buffer[strlen(input)] = '\0'; // Null-terminate explicitly after strncpy
    return strdup(buffer); // Allocate memory on the heap and return a copy
}

int main() {
    char *result;

    result = handleUserInput(10); // Test case 1
    printf("%s\n", result);
    free(result);

    result = handleUserInput(5); // Test case 2
    printf("%s\n", result);
    free(result);

    result = handleUserInput(20); // Test case 3
    printf("%s\n", result);
    free(result);


    result = handleUserInput(1); // Test case 4
    printf("%s\n", result);
    free(result);

    result = handleUserInput(0); // Test case 5
    printf("%s\n", result);
    if (result != NULL && result != "Input exceeds buffer size.") {
      free(result);
    }
    

    return 0;
}