// C code
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void terminate_process(int pid) {
    if (kill(pid, SIGTERM) == 0) {
        printf("Process %d terminated.\n", pid);
    } else {
        printf("Process with ID %d not found.\n", pid);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Please provide a single process ID as argument.\n");
        return 1;
    }

    int pid = atoi(argv[1]);
    if (pid <= 0) {
        printf("Invalid process ID. Please provide a numeric value.\n");
        return 1;
    }

    terminate_process(pid);
    return 0;
}