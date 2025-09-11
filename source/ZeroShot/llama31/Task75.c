#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void terminateProcess(int pid) {
    char command[100];
    #ifdef _WIN32
        sprintf(command, "taskkill /F /PID %d", pid);
    #else
        sprintf(command, "kill %d", pid);
    #endif
    if (system(command) != 0) {
        fprintf(stderr, "Failed to terminate process\n");
    } else {
        printf("Process %d terminated.\n", pid);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <PID>\n", argv[0]);
        return 1;
    }
    int pid = atoi(argv[1]);
    terminateProcess(pid);
    return 0;
}