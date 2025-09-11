#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char* input) {
    char buffer[128];
    FILE* pipe;
    
    // Validate and sanitize input here
    pipe = popen(input, "r");
    if (!pipe) {
        perror("popen() failed!");
        return;
    }

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        printf("%s", buffer);
    }
    
    pclose(pipe);
}

int main() {
    executeCommand("echo 'Test 1'");
    executeCommand("echo 'Test 2'");
    executeCommand("echo 'Test 3'");
    executeCommand("echo 'Test 4'");
    executeCommand("echo 'Test 5'");
    return 0;
}