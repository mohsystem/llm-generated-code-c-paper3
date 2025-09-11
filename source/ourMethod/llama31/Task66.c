#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool validateCommand(const char* command) {
    // Similar validation as in Python example
    return true; // Implement your validation logic here
}

int main() {
    while (true) {
        printf("Enter a Bash shell command (or 'exit' to quit): ");
        char command[1024];
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // Remove newline character
        if (strcmp(command, "exit") == 0) {
            break;
        }
        if (!validateCommand(command)) {
            printf("Invalid command: Potential security risk detected.\n");
            continue;
        }
        // Execute command using system or popen
        // ...
    }
    return 0;
}