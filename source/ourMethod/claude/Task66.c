
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_OUTPUT_LENGTH 4096
#define PATTERN "^[a-zA-Z0-9\\\\s_\\\\-./]+$"

bool isEmptyOrWhitespace(const char* str) {
    while (*str) {
        if (!isspace((unsigned char)*str)) {
            return false;
        }
        str++;
    }
    return true;
}

char* executeCommand(const char* command) {
    static char output[MAX_OUTPUT_LENGTH];
    output[0] = '\\0';

    // Check for null or empty command
    if (command == NULL || strlen(command) == 0 || isEmptyOrWhitespace(command)) {
        strncpy(output, "Error: Empty command", MAX_OUTPUT_LENGTH - 1);
        return output;
    }

    // Validate command length
    if (strlen(command) >= MAX_COMMAND_LENGTH) {
        strncpy(output, "Error: Command too long", MAX_OUTPUT_LENGTH - 1);
        return output;
    }

    // Validate command format using regex
    regex_t regex;
    int reti = regcomp(&regex, PATTERN, REG_EXTENDED);
    if (reti) {
        strncpy(output, "Error: Could not compile regex", MAX_OUTPUT_LENGTH - 1);
        return output;
    }

    reti = regexec(&regex, command, 0, NULL, 0);
    regfree(&regex);
    
    if (reti) {
        strncpy(output, "Error: Invalid command format - only alphanumeric characters, spaces, underscore, dash, dot and forward slash allowed", MAX_OUTPUT_LENGTH - 1);
        return output;
    }

    // Create command with bash
    char fullCommand[MAX_COMMAND_LENGTH + 50];
    snprintf(fullCommand, sizeof(fullCommand), "bash -c \\"%s\\"", command);

    // Execute command
    FILE* pipe = popen(fullCommand, "r");
    if (!pipe) {
        strncpy(output, "Error: Failed to open pipe for command execution", MAX_OUTPUT_LENGTH - 1);
        return output;
    }

    // Read output
    char buffer[128];
    output[0] = '\\0';
    
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        if (strlen(output) + strlen(buffer) >= MAX_OUTPUT_LENGTH - 1) {
            strncpy(output, "Error: Output too large", MAX_OUTPUT_LENGTH - 1);
            pclose(pipe);
            return output;
        }
        strcat(output, buffer);
    }

    // Close pipe and check status
    int status = pclose(pipe);
    if (status != 0) {
        char error[MAX_OUTPUT_LENGTH];
        snprintf(error, sizeof(error), "Error: Command execution failed with exit code %d", status);
        strncpy(output, error, MAX_OUTPUT_LENGTH - 1);
    }

    return output;
}

int main() {
    // Test cases
    const char* tests[] = {
        "ls -l",
        "pwd",
        "echo hello world",
        "date",
        "whoami"
    };
    
    int numTests = sizeof(tests) / sizeof(tests[0]);
    
    for (int i = 0; i < numTests; i++) {
        printf("Executing: %s\\n", tests[i]);
        printf("%s\\n", executeCommand(tests[i]));
        printf("-------------------\\n");
    }

    return 0;
}
