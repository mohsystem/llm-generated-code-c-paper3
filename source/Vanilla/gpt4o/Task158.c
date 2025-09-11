#include <stdio.h>
#include <stdlib.h>

char* runCommand(const char* command) {
    char* result = malloc(4096);
    if (result == NULL) {
        return "Error: Memory allocation failed!";
    }
    result[0] = '\0';
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        free(result);
        return "Error: popen() failed!";
    }
    char buffer[128];
    while (fgets(buffer, sizeof buffer, pipe) != NULL) {
        strcat(result, buffer);
    }
    pclose(pipe);
    return result;
}

int main() {
    printf("%s", runCommand("echo Test 1"));
    printf("%s", runCommand("echo Test 2"));
    printf("%s", runCommand("echo Test 3"));
    printf("%s", runCommand("echo Test 4"));
    printf("%s", runCommand("echo Test 5"));
    return 0;
}