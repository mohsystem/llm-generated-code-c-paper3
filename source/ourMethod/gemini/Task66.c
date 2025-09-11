#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* executeCommand(const char* command) {
    if (command == NULL || strlen(command) == 0) {
        char *error = (char*) malloc(sizeof(char) * 30);
        strcpy(error, "Error: Command cannot be empty.");
        return error;
    }


    // Basic validation for potentially dangerous characters
    if (strchr(command, ';') != NULL || strchr(command, '|') != NULL || strchr(command, '&') != NULL || strchr(command, '<') != NULL || strchr(command, '>') != NULL || strchr(command, '`') != NULL || strchr(command, '$') != NULL)
    {
       char *error = (char*) malloc(sizeof(char) * 30);
       strcpy(error, "Error: Invalid characters in command.");
       return error;
    }



    FILE* pipe = popen(command, "r");
    if (!pipe) {
        char *error = (char*) malloc(sizeof(char) * 33);
        strcpy(error, "Error: Failed to open pipe.");
        return error;

    }

    char buffer[128];
    char* result = (char*) malloc(sizeof(char) * 4096); // Start with a reasonable size
    size_t result_size = 4096;
    size_t result_len = 0;

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        size_t buffer_len = strlen(buffer);
        if (result_len + buffer_len >= result_size) {
            result_size *= 2;  // Double the size if needed
            result = (char*) realloc(result, result_size);
            if (result == NULL) {
                pclose(pipe);
                char *error = (char*) malloc(sizeof(char) * 33);
                strcpy(error, "Error: Memory allocation failed.");
                return error;
            }
        }
        strcpy(result + result_len, buffer);
        result_len += buffer_len;
    }

    pclose(pipe);
    return result;
}


int main() {
    char *testCases[] = {
            "ls -l",
            "pwd",
            "date",
            "whoami",
            "echo hello"
    };

    for (int i = 0; i < sizeof(testCases)/ sizeof(testCases[0]); i++){
        printf("Executing command: %s\n", testCases[i]);
        char *result = executeCommand(testCases[i]);
        printf("Result:\n%s", result);
        free(result); // Free allocated memory
    }

    // Example of invalid command (DO NOT uncomment and run this):
    char *invalidCommand = "rm -rf /";
    printf("Executing command: %s\n", invalidCommand);
    char *invalidResult = executeCommand(invalidCommand);
    printf("Result:\n%s", invalidResult);
    free(invalidResult);


    invalidCommand = "ls -l ; rm -rf /";
    printf("Executing command: %s\n", invalidCommand);
    invalidResult = executeCommand(invalidCommand);
    printf("Result:\n%s", invalidResult);
    free(invalidResult);


    return 0;
}