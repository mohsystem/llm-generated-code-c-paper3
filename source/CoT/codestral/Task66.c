// C
#include <stdio.h>
#include <stdlib.h>

int is_valid_command(const char* command) {
    // Add your validation logic here
    // For simplicity, this function always returns 1
    return 1;
}

void execute_command(const char* command) {
    if (is_valid_command(command)) {
        FILE* pipe = popen(command, "r");
        if (!pipe) return;
        char buffer[128];
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                printf("%s", buffer);
        }
        pclose(pipe);
    } else {
        printf("Invalid command\n");
    }
}

int main() {
    const char* command = "ls -l"; // replace with the command you want to execute
    execute_command(command);
    return 0;
}