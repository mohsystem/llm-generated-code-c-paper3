#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void executeCommand(const char* command) {
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        fprintf(stderr, "Failed to open pipe\n");
        return;
    }
    char buffer[128];
    while (fgets(buffer, 128, pipe) != NULL) {
        printf("%s", buffer);
    }
    pclose(pipe);
}

int main() {
    const char* allowedCommands[] = {"ls", "pwd", "date"};
    while (1) {
        char command[128];
        printf("Enter a command (ls, pwd, date) or 'exit' to quit: ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // Remove newline character

        if (strcmp(command, "exit") == 0) {
            break;
        }

        int isValid = 0;
        for (int i = 0; i < 3; ++i) {
            if (strcmp(command, allowedCommands[i]) == 0) {
                isValid = 1;
                break;
            }
        }

        if (isValid) {
            executeCommand(command);
        } else {
            printf("Invalid command. Please use one of the following: ls, pwd, date\n");
        }
    }
    return 0;
}