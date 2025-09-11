#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void executeCommand(const char* command) {
    // Basic validation (this is very limited and not secure for production use)
    if (!command || strchr(command, ';') || strchr(command, '&') || strchr(command, '|')) {
        printf("Invalid command format.\n");
        return;
    }

    char cmd[256];
    snprintf(cmd, sizeof(cmd), "bash -c '%s'", command);

    FILE* pipe = popen(cmd, "r");
    if (!pipe) {
        perror("Failed to open pipe.");
        return;
    }

    char buffer[128];
    while (fgets(buffer, 128, pipe) != NULL) {
        printf("%s", buffer);
    }
    pclose(pipe);
}

int main() {
    printf("Enter a Bash command: ");
    char command[256];
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = 0; // Remove newline character

    executeCommand(command);

    const char* testCommands[] = {
        "echo Hello World",
        "ls -l",
        "pwd",
        "invalid;command",
        "valid command"
    };

    for (int i = 0; i < 5; ++i) {
        printf("Command: %s\n", testCommands[i]);
        executeCommand(testCommands[i]);
        printf("\n");
    }

    return 0;
}