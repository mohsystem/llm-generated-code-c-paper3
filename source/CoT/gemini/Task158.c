#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char* executeCommand(const char* userInput) {
    // Basic sanitization (replace with more robust methods in real-world code)
     char* sanitizedInput = strdup(userInput); // Make a copy to modify
    char* ptr = sanitizedInput;
    while (*ptr) {
        if (*ptr == ';' || *ptr == '&' || *ptr == '|' || *ptr == '<' || *ptr == '>') {
            *ptr = ' '; // Replace dangerous characters with space
        }
        ptr++;
    }


    char* command = (char*)malloc(strlen(sanitizedInput) + 10); // Allocate memory
    sprintf(command, "/bin/sh -c \"%s\"", sanitizedInput); // Construct command string


    FILE* pipe = popen(command, "r"); // Open pipe for reading output
    if (pipe == NULL) {
        perror("popen failed");
        free(command);
        free(sanitizedInput);
        return strdup("Error executing command");
    }


    char buffer[128];
    char* output = NULL;
    size_t output_size = 0;

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        size_t buffer_len = strlen(buffer);
        char* new_output = (char*)realloc(output, output_size + buffer_len + 1);
        if (new_output == NULL) {
            perror("realloc failed");
            pclose(pipe);
            free(output);
            free(command);
            free(sanitizedInput);
            return strdup("Memory allocation error");
        }
        output = new_output;
        memcpy(output + output_size, buffer, buffer_len);
        output_size += buffer_len;
        output[output_size] = '\0'; // Null-terminate
    }

    int status = pclose(pipe);
    if (status != 0) {
        char* error_message = (char*) malloc(100);
        snprintf(error_message, 100, "Command execution failed with exit code: %d", WEXITSTATUS(status));

        free(command);
        free(sanitizedInput);
        if (output != NULL) {
            free(output);
        }

        return error_message;
    }


    free(command);
    free(sanitizedInput);

    return output; // Return command output
}

int main() {
    char* testCases[] = {"ls -l", "pwd", "whoami", "date", "echo hello"};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        printf("Test case %d: %s\n", i + 1, testCases[i]);
        char* output = executeCommand(testCases[i]);

        if (output != NULL) {
            printf("%s", output);
            free(output);  // Free allocated memory
        }

        printf("\n");
    }

    return 0;
}