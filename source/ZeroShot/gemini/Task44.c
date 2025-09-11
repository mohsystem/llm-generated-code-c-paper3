#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to reverse a string
void reverse_string(char *str) {
    int start = 0;
    int end = strlen(str) - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}


char* processInput(char* input) {
    if (input == NULL || strlen(input) == 0 || (strspn(input, " ") == strlen(input)) ) {
        return "Invalid input: Input cannot be empty or contain only whitespace.";
    }

    // Perform operations on the validated input (example: reversing the string)
    char* reversed_input = strdup(input); // Allocate memory and copy to prevent modification of original
    if (reversed_input == NULL) {
        return "Memory allocation failed"; // Handle memory allocation error
    }

    reverse_string(reversed_input);
    return reversed_input;
}

int main() {
    char input[1000]; // Adjust size as needed
    printf("Enter a string:\n");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }
    // Remove the trailing newline from fgets
    input[strcspn(input, "\n")] = 0;

    char* result = processInput(input);
    printf("Processed string: %s\n", result);

    // Test cases
    printf("%s\n", processInput("hello"));
    printf("%s\n", processInput("world"));
    printf("%s\n", processInput(""));
    printf("%s\n", processInput("   "));
    printf("%s\n", processInput("12345"));

    // Free allocated memory if strdup was used
    if (strcmp(result, "Invalid input: Input cannot be empty or contain only whitespace.") != 0 && strcmp(result, "Memory allocation failed") != 0)
         free(result);
    return 0;
}