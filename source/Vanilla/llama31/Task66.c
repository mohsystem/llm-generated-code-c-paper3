#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int executeBashCommand(const char* command) {
    char fullCommand[256];
    snprintf(fullCommand, sizeof(fullCommand), "bash -c '%s'", command);

    FILE* pipe = popen(fullCommand, "r");
    if (!pipe) {
        fprintf(stderr, "Failed to open pipe\n");
        return 1;
    }

    char buffer[128];
    while (fgets(buffer, 128, pipe) != NULL) {
        printf("%s", buffer);
    }
    pclose(pipe);

    return 0;
}

int main() {
    char command[256];
    printf("Enter a Bash command: ");
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = 0; // Remove newline character

    // Validate the command (basic validation, you can add more)
    if (command[0] == '\0') {
        printf("Invalid command\n");
        return 1;
    }

    executeBashCommand(command);

    return 0;
}