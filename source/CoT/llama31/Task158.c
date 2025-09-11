#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Function to split the string into arguments
char** splitString(const char* str, int* argc) {
    if (str == NULL) return NULL;

    int count = 1;
    for (int i = 0; str[i]; ++i) {
        if (str[i] == ' ') count++;
    }

    char** args = malloc((count + 1) * sizeof(char*));
    if (args == NULL) return NULL;

    args[count] = NULL;
    const char* ptr = str;
    for (int i = 0; i < count; ++i) {
        while (*ptr == ' ') ++ptr;
        const char* start = ptr;
        while (*ptr && *ptr != ' ') ++ptr;
        args[i] = strndup(start, ptr - start);
        if (args[i] == NULL) {
            for (int j = 0; j < i; ++j) free(args[j]);
            free(args);
            return NULL;
        }
    }

    *argc = count;
    return args;
}

int executeCommand(const char* command, char** args, int argc) {
    // Validate input to prevent security vulnerabilities
    if (command == NULL || args == NULL || argc == 0) {
        fprintf(stderr, "Invalid input. Please provide a valid command and arguments.\n");
        return 1;
    }

    // Execute the command securely
    try {
        pid_t pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Error forking process.\n");
            return 1;
        }

        if (pid == 0) {
            // Child process
            execvp(command, args);
            fprintf(stderr, "Error executing command: %s\n", command);
            _exit(1);
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) {
                printf("Command executed with exit code: %d\n", WEXITSTATUS(status));
                return WEXITSTATUS(status);
            } else {
                fprintf(stderr, "Error waiting for child process.\n");
                return 1;
            }
        }
    } catch (const std::exception& e) {
        fprintf(stderr, "Error executing command: %s\n", e.what());
        return 1;
    }
}

int main() {
    printf("Enter the OS command: ");
    char command[1024];
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = 0; // Remove the newline character

    printf("Enter the arguments (separated by spaces): ");
    char argsStr[1024];
    fgets(argsStr, sizeof(argsStr), stdin);
    argsStr[strcspn(argsStr, "\n")] = 0; // Remove the newline character

    int argc;
    char** arguments = splitString(argsStr, &argc);

    if (arguments == NULL) {
        fprintf(stderr, "Error splitting arguments.\n");
        return 1;
    }

    int result = executeCommand(command, arguments, argc);

    for (int i = 0; i < argc; ++i) free(arguments[i]);
    free(arguments);

    return result;
}