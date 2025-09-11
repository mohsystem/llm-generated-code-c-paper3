
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

char* execute_command(const char* command) {
    if (command == NULL || strlen(command) == 0) {
        return strdup("Invalid command: Command cannot be empty");
    }

    char buffer[BUFFER_SIZE];
    char* result = malloc(BUFFER_SIZE);
    result[0] = '\\0';
    
    // Prepare bash command
    char bash_command[BUFFER_SIZE + 6];
    snprintf(bash_command, sizeof(bash_command), "bash -c \\"%s\\"", command);
    
    FILE* pipe = popen(bash_command, "r");
    if (!pipe) {
        return strdup("Error executing command: Failed to open pipe");
    }

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        if (strlen(result) + strlen(buffer) >= BUFFER_SIZE) {
            char* new_result = realloc(result, strlen(result) + BUFFER_SIZE);
            if (new_result == NULL) {
                free(result);
                pclose(pipe);
                return strdup("Error: Memory allocation failed");
            }
            result = new_result;
        }
        strcat(result, buffer);
    }

    pclose(pipe);
    return result;
}

int main() {
    // Test cases
    const char* test_commands[] = {
        "ls -l",
        "pwd",
        "echo 'Hello World'",
        "date",
        "whoami"
    };

    for (int i = 0; i < 5; i++) {
        printf("Test case %d: %s\\n", i + 1, test_commands[i]);
        printf("Output:\\n");
        char* output = execute_command(test_commands[i]);
        printf("%s", output);
        printf("------------------------\\n");
        free(output);
    }

    return 0;
}
