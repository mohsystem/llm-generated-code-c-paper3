
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_OUTPUT_LENGTH 1024
#define NUM_ALLOWED_COMMANDS 4

// Whitelist of allowed commands
const char* allowedCommands[] = {"date", "time", "pwd", "whoami"};

void sanitizeInput(const char* input, char* output) {
    int j = 0;
    for(int i = 0; input[i] != '\\0'; i++) {
        if(isalpha((unsigned char)input[i])) {
            output[j++] = tolower((unsigned char)input[i]);
        }
    }
    output[j] = '\\0';
}

int isCommandAllowed(const char* command) {
    for(int i = 0; i < NUM_ALLOWED_COMMANDS; i++) {
        if(strcmp(command, allowedCommands[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void executeCommand(const char* userInput, char* output) {
    char sanitizedInput[MAX_COMMAND_LENGTH] = {0};
    sanitizeInput(userInput, sanitizedInput);
    
    // Validate against whitelist
    if(!isCommandAllowed(sanitizedInput)) {
        strcpy(output, "Error: Command not allowed");
        return;
    }
    
    // Execute command securely
    #ifdef _WIN32
        char cmd[MAX_COMMAND_LENGTH] = "";
        strncpy(cmd, sanitizedInput, MAX_COMMAND_LENGTH - 1);
    #else
        char cmd[MAX_COMMAND_LENGTH] = "/bin/";
        strncat(cmd, sanitizedInput, MAX_COMMAND_LENGTH - 6);
    #endif
    
    FILE* pipe = popen(cmd, "r");
    if(!pipe) {
        strcpy(output, "Error: Failed to execute command");
        return;
    }
    
    char buffer[MAX_OUTPUT_LENGTH] = {0};
    if(fgets(buffer, sizeof(buffer), pipe) != NULL) {
        strncpy(output, buffer, MAX_OUTPUT_LENGTH - 1);
    } else {
        strcpy(output, "No output from command");
    }
    
    pclose(pipe);
}

int main() {
    char output[MAX_OUTPUT_LENGTH];
    const char* testInputs[] = {
        "date",
        "pwd",
        "rm -rf /",  // malicious command
        "whoami; rm -rf /",  // command injection attempt
        "; destructive_command"  // another injection attempt
    };
    
    for(int i = 0; i < 5; i++) {
        printf("Input: %s\\n", testInputs[i]);
        executeCommand(testInputs[i], output);
        printf("Output: %s\\n\\n", output);
    }
    
    return 0;
}
