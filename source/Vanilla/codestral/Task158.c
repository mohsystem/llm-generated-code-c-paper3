#include <stdlib.h>
#include <stdio.h>

void execute_command(char* command) {
    int result = system(command);
    if (result == -1) {
        fprintf(stderr, "Error executing command.\n");
    }
}

int main() {
    execute_command("ls");
    execute_command("dir");
    execute_command("pwd");
    execute_command("echo 'Hello, World!'");
    execute_command("cal");
    return 0;
}