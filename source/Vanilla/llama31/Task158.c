#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void executeCommand(const char* command) {
    system(command);
}

int main() {
    // Test cases
    const char* commands[] = {"ls -l", "echo Hello World!", "pwd", "cat /etc/hosts", "date"};

    for (int i = 0; i < 5; ++i) {
        printf("Executing command: %s\n", commands[i]);
        executeCommand(commands[i]);
    }

    // User input
    char userInput[1024];
    printf("Enter a command: ");
    fgets(userInput, sizeof(userInput), stdin);
    userInput[strcspn(userInput, "\n")] = 0; // Remove newline character
    printf("Executing command: %s\n", userInput);
    executeCommand(userInput);

    return 0;
}