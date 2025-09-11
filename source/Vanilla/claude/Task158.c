
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* executeCommand(char* input) {
    // Unsafe command execution with user input
    system(input);
    char* result = (char*)malloc(strlen("Command executed: ") + strlen(input) + 1);
    strcpy(result, "Command executed: ");
    strcat(result, input);
    return result;
}

int main() {
    // Test cases
    printf("%s\\n", executeCommand("dir"));
    printf("%s\\n", executeCommand("echo hello")); 
    printf("%s\\n", executeCommand("type test.txt"));
    printf("%s\\n", executeCommand("whoami"));
    printf("%s\\n", executeCommand("hostname"));
    return 0;
}
