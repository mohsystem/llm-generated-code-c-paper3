#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isValidCommand(const char *command) {
    if (strstr(command, ";") != NULL || 
        strstr(command, "&") != NULL || 
        strstr(command, "|") != NULL) {
        return false;
    }
    return true;
}

char* executeCommand(const char *command) {
    if (!isValidCommand(command)) {
        return "Invalid command!";
    }

    char buffer[128];
    char *result = malloc(1024);
    result[0] = '\0';

    FILE *pipe = popen(command, "r");
    if (!pipe) {
        return "popen() failed!";
    }
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        strcat(result, buffer);
    }
    pclose(pipe);
    return result;
}

int main() {
    printf("%s", executeCommand("echo Hello World"));
    printf("%s", executeCommand("ls"));
    printf("%s", executeCommand("pwd"));
    printf("%s", executeCommand("whoami"));
    printf("%s", executeCommand("invalid;command"));
    return 0;
}