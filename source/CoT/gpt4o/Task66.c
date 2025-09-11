#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int isValidCommand(const char *command) {
    regex_t regex;
    int reti;

    // Compile regex
    reti = regcomp(&regex, "^[a-zA-Z0-9_\\- ]+$", REG_EXTENDED);
    if (reti) {
        return 0;
    }

    // Execute regex
    reti = regexec(&regex, command, 0, NULL, 0);
    regfree(&regex);
    return !reti;
}

char* executeCommand(const char *command) {
    if (isValidCommand(command)) {
        char buffer[128];
        char *result = malloc(1024);
        result[0] = '\0';
        FILE *pipe = popen(command, "r");
        if (!pipe) {
            strcpy(result, "Error: popen() failed!");
            return result;
        }
        while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
            strcat(result, buffer);
        }
        pclose(pipe);
        return result;
    }
    return "Invalid command.";
}

int main() {
    printf("%s\n", executeCommand("echo Hello"));
    printf("%s\n", executeCommand("ls"));
    printf("%s\n", executeCommand("pwd"));
    printf("%s\n", executeCommand("whoami"));
    printf("%s\n", executeCommand("uname -a"));
    return 0;
}