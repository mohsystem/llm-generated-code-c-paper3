#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("No process ID provided.\n");
        return;
    }

    char* endptr;
    long pid = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0') {
        printf("Invalid process ID provided.\n");
        return;
    }

    if (kill(pid, SIGTERM) == 0) {
        printf("Process %ld terminated successfully.\n", pid);
    } else {
        printf("Failed to terminate process %ld.\n", pid);
    }
}