#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char* command) {
    char buffer[128];
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        printf("Error executing command.\n");
        return;
    }
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        printf("%s", buffer);
    }
    pclose(pipe);
}

int main() {
    executeCommand("echo Hello World");
    executeCommand("pwd");
    executeCommand("ls");
    executeCommand("whoami");
    executeCommand("date");
    return 0;
}