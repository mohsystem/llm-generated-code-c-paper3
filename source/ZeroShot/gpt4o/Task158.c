#include <stdio.h>
#include <stdlib.h>

void executeCommandSecurely(const char* input) {
    char command[256];
    snprintf(command, sizeof(command), "echo %s", input);
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        printf("popen() failed!\n");
        return;
    }
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        printf("%s", buffer);
    }
    pclose(pipe);
}

int main() {
    char input[100];
    for (int i = 0; i < 5; ++i) {
        printf("Enter input: ");
        fgets(input, sizeof(input), stdin);
        // Remove newline character if present
        input[strcspn(input, "\n")] = '\0';
        printf("Output: ");
        executeCommandSecurely(input);
        printf("\n");
    }
    return 0;
}