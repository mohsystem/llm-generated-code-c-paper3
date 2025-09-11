
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_OUTPUT_LENGTH 4096
#define NUM_ALLOWED_COMMANDS 5

const char* ALLOWED_COMMANDS[] = {"ls", "pwd", "date", "whoami", "echo"};

int is_command_allowed(const char* cmd) {
    char base_cmd[MAX_COMMAND_LENGTH];
    int i = 0;
    
    // Extract base command
    while (cmd[i] != ' ' && cmd[i] != '\\0' && i < MAX_COMMAND_LENGTH - 1) {
        base_cmd[i] = tolower(cmd[i]);
        i++;
    }
    base_cmd[i] = '\\0';
    
    // Check if command is in allowed list
    for (i = 0; i < NUM_ALLOWED_COMMANDS; i++) {
        if (strcmp(base_cmd, ALLOWED_COMMANDS[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

char* execute_command(const char* command) {
    static char output[MAX_OUTPUT_LENGTH];
    
    // Validate input
    if (command == NULL || strlen(command) == 0) {
        strcpy(output, "Invalid command: Command cannot be empty");
        return output;
    }
    
    if (strlen(command) >= MAX_COMMAND_LENGTH) {
        strcpy(output, "Invalid command: Command too long");
        return output;
    }
    
    // Security check
    if (!is_command_allowed(command)) {
        strcpy(output, "Command not allowed for security reasons");
        return output;
    }
    
    // Execute command
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        strcpy(output, "Error executing command");
        return output;
    }
    
    // Read output
    char* result = fgets(output, MAX_OUTPUT_LENGTH, pipe);
    if (result == NULL) {
        strcpy(output, "No output from command");
    }
    
    pclose(pipe);
    return output;
}

int main() {
    // Test cases
    const char* test_commands[] = {
        "ls",
        "pwd",
        "date",
        "whoami",
        "rm -rf /" // should be rejected
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Executing: %s\\n", test_commands[i]);
        printf("Result: %s\\n", execute_command(test_commands[i]));
        printf("------------------------\\n");
    }
    
    return 0;
}
