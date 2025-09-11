#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* executeCommand(const char* command) {
    if (!isValidCommand(command)) {
        return strdup("Invalid command format or potentially harmful command.");
    }

    char buffer[128];
    char* result = NULL;
    size_t result_len = 0;
    
    FILE* pipe = popen((char*) (strcat(strdup("/bin/bash -c \""), command) + "\""), "r");
    if (!pipe) {
       return strdup("Command execution failed.");
    }

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        size_t buffer_len = strlen(buffer);
        char *new_result = realloc(result, result_len + buffer_len + 1);
        if (!new_result) {
            free(result);
            pclose(pipe);
            return strdup("Memory allocation failed.");
        }
        result = new_result;
        memcpy(result + result_len, buffer, buffer_len);
        result_len += buffer_len;
        result[result_len] = '\0'; 
    }
    pclose(pipe);
    return result;
}

int isValidCommand(const char* command) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "[|;&<>`$()]", 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 0; // Return 0 if regex compilation fails
    }

    reti = regexec(&regex, command, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
       return 0; // Disallowed patterns found
    }

    reti = regcomp(&regex, "^(ls|date|pwd|whoami)(\\s+.*)?$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }
    reti = regexec(&regex, command, 0, NULL, 0);
    regfree(&regex);
    if (reti == REG_NOMATCH) {
        return 0;
    }

    return 1;
}

int main() {
    char *testCommands[] = {
        "ls -l",
        "date",
        "pwd",
        "whoami",
        "rm -rf /"  // Invalid command
    };
    int numCommands = sizeof(testCommands) / sizeof(testCommands[0]);

    for (int i = 0; i < numCommands; i++) {
        printf("Command: %s\n", testCommands[i]);
        char* result = executeCommand(testCommands[i]);
        printf("Result:\n%s\n", result ? result : "Command execution failed");
        free(result); // Free the allocated memory
        printf("---\n");

    }

    return 0;
}