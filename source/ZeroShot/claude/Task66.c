
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

#define MAX_BUFFER 4096
#define MAX_COMMAND_LENGTH 256

int is_valid_command(const char* command) {
    if (command == NULL || strlen(command) == 0) {
        return 0;
    }

    regex_t regex;
    int ret;

    // Compile regular expression
    ret = regcomp(&regex, "^[a-zA-Z0-9\\\\s\\\\-_./]*$", REG_EXTENDED);
    if (ret) {
        return 0;
    }

    // Execute regular expression
    ret = regexec(&regex, command, 0, NULL, 0);
    regfree(&regex);

    return ret == 0;
}

int is_allowed_command(const char* command) {
    const char* allowed_commands[] = {"ls", "pwd", "whoami", "date"};
    int num_commands = 4;
    char cmd_copy[MAX_COMMAND_LENGTH];
    strncpy(cmd_copy, command, MAX_COMMAND_LENGTH - 1);
    cmd_copy[MAX_COMMAND_LENGTH - 1] = '\\0';
    
    char* base_cmd = strtok(cmd_copy, " ");
    if (base_cmd == NULL) {
        return 0;
    }

    for (int i = 0; i < num_commands; i++) {
        if (strcmp(base_cmd, allowed_commands[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

char* execute_command(const char* command) {
    static char buffer[MAX_BUFFER];
    buffer[0] = '\\0';

    if (!is_valid_command(command)) {
        strncpy(buffer, "Invalid command format", MAX_BUFFER - 1);
        return buffer;
    }

    if (!is_allowed_command(command)) {
        strncpy(buffer, "Command not allowed for security reasons", MAX_BUFFER - 1);
        return buffer;
    }

    FILE* pipe = popen(command, "r");
    if (!pipe) {
        strncpy(buffer, "Command execution failed", MAX_BUFFER - 1);
        return buffer;
    }

    char temp[MAX_BUFFER];
    buffer[0] = '\\0';
    while (fgets(temp, sizeof(temp), pipe) != NULL) {
        if (strlen(buffer) + strlen(temp) < MAX_BUFFER - 1) {
            strcat(buffer, temp);
        }
    }

    pclose(pipe);
    return buffer;
}

int main() {
    // Test cases
    const char* test_commands[] = {
        "ls -l",
        "pwd",
        "whoami",
        "date",
        "rm -rf /" // Should be rejected
    };
    int num_tests = 5;

    for (int i = 0; i < num_tests; i++) {
        printf("Executing: %s\\n", test_commands[i]);
        printf("Result:\\n%s\\n", execute_command(test_commands[i]));
        printf("------------------------\\n");
    }

    return 0;
}
