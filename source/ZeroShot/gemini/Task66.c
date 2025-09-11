#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* executeCommand(const char* command) {
    if (!isValidCommand(command)) {
        return "Invalid command";
    }
    char buffer[128];
    char* result = NULL;
    size_t result_size = 0;
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        return "Error: popen() failed!";
    }

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        size_t buffer_len = strlen(buffer);
        char* new_result = realloc(result, result_size + buffer_len + 1); 
        if (!new_result) {
            free(result); // Free previously allocated memory
            pclose(pipe);
            return "Error: Memory allocation failed";
        }
        result = new_result;
        memcpy(result + result_size, buffer, buffer_len);
        result_size += buffer_len;
        result[result_size] = '\0';
    }
    pclose(pipe);
    return result;
}


int isValidCommand(const char* command) {
    // Basic validation
    return command != NULL && strlen(command) > 0 && strpbrk(command, ";|&><") == NULL;
}

int main() {
    printf("%s\n", executeCommand("ls -l"));
    printf("%s\n", executeCommand("pwd"));
    printf("%s\n", executeCommand("date"));
    printf("%s\n", executeCommand("whoami"));
    printf("%s\n", executeCommand("; rm -rf *")); // Invalid
    return 0;
}