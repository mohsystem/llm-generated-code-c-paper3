#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void executeCommand(const char* command) {
    // Use system to execute the command, but be cautious of security risks
    // For security, consider using fork and exec instead of system
    if (system(command) != 0) {
        fprintf(stderr, "Error executing command: %s\n", command);
    } else {
        printf("Command executed successfully.\n");
    }
}

int main() {
    char command[1024];
    printf("Enter the OS command: ");
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = 0; // Remove the newline character

    // Validate the input to prevent security weaknesses
    if (strlen(command) == 0) {
        printf("Invalid input. Please provide a valid command.\n");
        return 1;
    }

    executeCommand(command);
    return 0;
}