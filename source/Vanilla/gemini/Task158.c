#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* executeCommand(const char* command) {
    FILE *pipe = popen(command, "r");
    if (!pipe) {
        perror("popen failed");
        return NULL;
    }

    char buffer[128];
    char *result = (char*)malloc(1); // Start with a small allocation
    size_t result_size = 1;
    result[0] = '\0';


    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        size_t buffer_len = strlen(buffer);
        char *temp = (char*)realloc(result, result_size + buffer_len);
        if(temp == NULL) {
            free(result);
            pclose(pipe);
            return NULL;
        }
        result = temp;
        strcat(result, buffer);
        result_size += buffer_len;
    }

    pclose(pipe);
    return result;
}

int main() {
    char commands[5][128];
    for (int i = 0; i < 5; i++) {
        printf("Enter command %d: ", i + 1);
        fgets(commands[i], sizeof(commands[i]), stdin);
        commands[i][strcspn(commands[i], "\n")] = 0; // Remove trailing newline
    }

    for (int i = 0; i < 5; i++) {
        printf("Executing command: %s\n", commands[i]);
        char *output = executeCommand(commands[i]);
        if (output != NULL) {
            printf("Output:\n%s\n", output);
            free(output); // Free allocated memory
        }
    }
    return 0;
}