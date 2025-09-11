
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_OUTPUT_LENGTH 1024
#define ALLOWED_COMMANDS_COUNT 4

const char* ALLOWED_COMMANDS[] = {"dir", "ls", "pwd", "date"};

bool isAllowedCommand(const char* command) {
    for (int i = 0; i < ALLOWED_COMMANDS_COUNT; i++) {
        if (strcmp(command, ALLOWED_COMMANDS[i]) == 0) {
            return true;
        }
    }
    return false;
}

bool isAlphabetic(const char* str) {
    while (*str) {
        if (!isalpha((unsigned char)*str)) {
            return false;
        }
        str++;
    }
    return true;
}

char* executeCommand(const char* userInput) {
    static char output[MAX_OUTPUT_LENGTH];
    output[0] = '\\0';
    
    // Input validation
    if (userInput == NULL || strlen(userInput) == 0) {
        strcpy(output, "Invalid input: Command cannot be empty");
        return output;
    }
    
    if (strlen(userInput) >= MAX_COMMAND_LENGTH) {
        strcpy(output, "Invalid input: Command too long");
        return output;
    }
    
    // Sanitize input - only allow alphabetic characters
    if (!isAlphabetic(userInput)) {
        strcpy(output, "Invalid input: Only letters are allowed");
        return output;
    }
    
    // Convert to lowercase
    char sanitizedCommand[MAX_COMMAND_LENGTH];
    strcpy(sanitizedCommand, userInput);
    for (int i = 0; sanitizedCommand[i]; i++) {
        sanitizedCommand[i] = tolower(sanitizedCommand[i]);
    }
    
    // Check if command is in whitelist
    if (!isAllowedCommand(sanitizedCommand)) {
        strcpy(output, "Command not allowed. Allowed commands: ");
        for (int i = 0; i < ALLOWED_COMMANDS_COUNT; i++) {
            strcat(output, ALLOWED_COMMANDS[i]);
            if (i < ALLOWED_COMMANDS_COUNT - 1) {
                strcat(output, ", ");
            }
        }
        return output;
    }
    
    // Execute command
    #ifdef _WIN32
        char fullCommand[MAX_COMMAND_LENGTH + 10];
        sprintf(fullCommand, "cmd /c %s", sanitizedCommand);
    #else
        char fullCommand[MAX_COMMAND_LENGTH + 10];
        sprintf(fullCommand, "bash -c %s", sanitizedCommand);
    #endif
    
    FILE* pipe = popen(fullCommand, "r");
    if (!pipe) {
        strcpy(output, "Error executing command");
        return output;
    }
    
    char buffer[128];
    output[0] = '\\0';
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        if (strlen(output) + strlen(buffer) < MAX_OUTPUT_LENGTH) {
            strcat(output, buffer);
        }
    }
    
    pclose(pipe);
    return output;
}

int main() {
    // Test cases
    const char* testInputs[] = {
        "ls",
        "dir",
        "pwd",
        "date",
        "rm"  // This should be rejected
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Test input: %s\\n", testInputs[i]);
        printf("Output: %s\\n", executeCommand(testInputs[i]));
        printf("------------------------\\n");
    }
    
    return 0;
}
