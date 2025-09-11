// This is a simplified example and doesn't include any security measures.
// A real-world application would need to include proper command validation and error handling.

#include <stdio.h>
#include <string.h>

char* execute_command(const char* command) {
    if (strcmp(command, "ls") == 0) {
        FILE* pipe = popen("ls", "r");
        if (!pipe) return "popen failed!";
        char buffer[128];
        char* result = malloc(sizeof(char) * 128);
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                strcat(result, buffer);
        }
        pclose(pipe);
        return result;
    } else {
        return "Command not found.";
    }
}

int main() {
    printf("%s", execute_command("ls"));
    return 0;
}