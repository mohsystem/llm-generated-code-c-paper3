#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100

int main() {
    char input[MAX_INPUT_LENGTH];
    printf("Enter data to be used in an OS command: ");
    fgets(input, MAX_INPUT_LENGTH, stdin);

    // Remove trailing newline character
    input[strcspn(input, "\n")] = 0;

    // Use system function to run OS command, be aware of command injection
    char command[MAX_INPUT_LENGTH + 20];
    snprintf(command, sizeof(command), "your_os_command %s", input);
    int result = system(command);

    if (result == -1) {
        fprintf(stderr, "Error executing command\n");
        return 1;
    } else {
        printf("Command executed with return code: %d\n", result);
        return 0;
    }
}