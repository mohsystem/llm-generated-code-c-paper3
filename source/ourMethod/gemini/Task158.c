#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to remove null bytes from a string
void remove_null_bytes(char *str) {
    char *p = str;
    while (*p) {
        if (*p == '\0') {
            *p = ' '; // Replace with a space
        }
        p++;
    }
}


char* executeOSCommand(const char *userInput) {
    char *sanitizedInput = strdup(userInput); // Make a copy to avoid modifying the original
    remove_null_bytes(sanitizedInput); // Remove null bytes

    // Execute command using popen
    char *command = (char *)malloc(strlen(sanitizedInput) + 10); // Allocate memory for the command
    if (!command) return "Memory allocation failed";
    sprintf(command, "cmd.exe /c %s", sanitizedInput);  // Prepend "cmd.exe /c" for Windows

    FILE *pipe = _popen(command, "r");  // Use _popen on Windows
    if (!pipe) {
        free(command);
        free(sanitizedInput);
        return "Error executing command";
    }

    char *output = NULL;
    size_t output_size = 0;
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        size_t buffer_len = strlen(buffer);
        char *new_output = (char *)realloc(output, output_size + buffer_len + 1);
        if (!new_output) {
            free(output);
            free(command);
            free(sanitizedInput);
            _pclose(pipe);
            return "Memory allocation failed";
        }
        output = new_output;
        memcpy(output + output_size, buffer, buffer_len);
        output_size += buffer_len;
        output[output_size] = '\0';
    }


    int returnCode = _pclose(pipe); // Use _pclose on Windows

    if (returnCode != 0) {
        size_t message_len = strlen("Command execution failed with exit code: ");
        char* new_output = realloc(output, output_size + message_len + 12);
        if (!new_output) {
            free(output);
            return "Memory allocation failed";
        }

        output = new_output;
        sprintf(output + output_size, "Command execution failed with exit code: %d\n", returnCode);
    }
    free(command);
    free(sanitizedInput);
    return output;
}

int main() {
    // Test cases
    const char *testInputs[] = {
        "echo Hello, world!",
        "dir",
        "whoami",
        "ipconfig",
        "notepad"
    };

    for (int i = 0; i < sizeof(testInputs) / sizeof(testInputs[0]); i++) {
        printf("Executing command: %s\n", testInputs[i]);
        char *result = executeOSCommand(testInputs[i]);
        printf("%s---\n", result);
        free(result); // Free the allocated memory
    }

    return 0;
}