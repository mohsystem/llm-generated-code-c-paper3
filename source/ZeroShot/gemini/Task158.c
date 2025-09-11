#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// A very basic (and insecure in general) example.  DO NOT use this in real code.
// Demonstrates the concept of sanitizing input. In real-world scenarios, much more robust sanitization and execution methods are required.
char* executeSafeCommand(const char* userInput) {
    // Sanitize user input to prevent command injection vulnerabilities (very basic example)
    char* sanitizedInput = strdup(userInput); // Allocate memory for a copy
    for (size_t i = 0; sanitizedInput[i] != '\0'; i++) {
        if (sanitizedInput[i] == ';' || sanitizedInput[i] == '&' || sanitizedInput[i] == '|' || sanitizedInput[i] == '`' || sanitizedInput[i] == '$' || sanitizedInput[i] == '\\' || sanitizedInput[i] == '(' || sanitizedInput[i] == ')') {
            sanitizedInput[i] = ' '; // Replace potentially dangerous characters with spaces
        }
    }


    // Note: This is for demonstration ONLY. In real code, use execvp or similar.
    char* command = (char*)malloc(strlen(sanitizedInput) + 6); // Allocate memory
    strcpy(command, "echo ");
    strcat(command, sanitizedInput);
    free(sanitizedInput);


    return command;

}

int main() {
    char* result1 = executeSafeCommand("test1");
    printf("%s\n", result1);
    free(result1);

    char* result2 = executeSafeCommand("test2; ls -l");
    printf("%s\n", result2);
    free(result2);

    char* result3 = executeSafeCommand("test3 | rm -rf /");
    printf("%s\n", result3);
    free(result3);


    char* result4 = executeSafeCommand("test4 && cat /etc/passwd");
    printf("%s\n", result4);
    free(result4);

    char* result5 = executeSafeCommand("test5$(whoami)");
    printf("%s\n", result5);
    free(result5);


    return 0;
}