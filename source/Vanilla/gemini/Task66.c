#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* executeCommand(const char* command) {
    char* result = NULL;
    char buffer[128];
    FILE* pipe = popen(command, "r");

    if (!pipe) {
        return strdup("Error executing command."); // Allocate memory for the error message
    }

    size_t buffer_size = 128;
    size_t result_size = 0;
    result = (char*)malloc(buffer_size);
    if (result == NULL) {
        pclose(pipe);
        return strdup("Memory allocation error.");
    }
    result[0] = '\0'; // Initialize as empty string

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        size_t len = strlen(buffer);
        if (result_size + len + 1 > buffer_size) {
            buffer_size *= 2;
            char* temp = (char*)realloc(result, buffer_size);
            if (temp == NULL) {
                pclose(pipe);
                free(result);
                return strdup("Memory allocation error.");
            }
            result = temp;
        }
        strcat(result, buffer);
        result_size += len;
    }

    int returnCode = pclose(pipe);
    if (returnCode != 0) {
        char error_message[128];
        snprintf(error_message, sizeof(error_message), "Error executing command. Return code: %d", returnCode);
        free(result);
        return strdup(error_message);
    }


    return result;
}

int main() {
    const char* testCommands[] = {
        "ls -l",
        "pwd",
        "date",
        "echo hello",
        "cat non_existent_file" // Example of an error case
    };
    int numCommands = sizeof(testCommands) / sizeof(testCommands[0]);

    for (int i = 0; i < numCommands; i++) {
        printf("Executing command: %s\n", testCommands[i]);
        char* result = executeCommand(testCommands[i]);
        printf("Result:\n%s\n", result);
        free(result); // Free allocated memory
    }

    return 0;
}