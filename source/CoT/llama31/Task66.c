#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validateCommand(const char* command) {
    // Basic validation, should be more robust in real scenarios
    return strstr(command, "rm") == NULL && strstr(command, "rm -rf") == NULL;
}

void executeCommand(const char* command) {
    system(command);
}

int main() {
    // Test cases
    char* commands[] = {"ls -l", "echo Hello World", "invalid command", "rm -rf /"};

    for (int i = 0; i < 4; i++) {
        if (validateCommand(commands[i])) {
            printf("Command: %s\n", commands[i]);
            executeCommand(commands[i]);
        } else {
            printf("Invalid command: %s\n", commands[i]);
        }
    }

    return 0;
}