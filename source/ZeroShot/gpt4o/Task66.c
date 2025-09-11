#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool validateCommand(const char* command) {
    // Simple validation example: allow only 'ls' and 'echo' commands
    return strncmp(command, "ls", 2) == 0 || strncmp(command, "echo", 4) == 0;
}

char* executeShellCommand(const char* command) {
    if (!validateCommand(command)) {
        return "Invalid command";
    }

    char buffer[128];
    char* result = malloc(1024);
    result[0] = '\0';
    FILE* pipe = popen(command, "r");
    if (!pipe) return "Error executing command";
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        strcat(result, buffer);
    }
    pclose(pipe);
    return result;
}

int main() {
    printf("%s\n", executeShellCommand("ls"));
    printf("%s\n", executeShellCommand("echo Hello, World!"));
    printf("%s\n", executeShellCommand("rm -rf /"));
    printf("%s\n", executeShellCommand("echo Secure Coding"));
    printf("%s\n", executeShellCommand("pwd"));
    return 0;
}