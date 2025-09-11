#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int terminateProcess(pid_t pid) {
    if (kill(pid, SIGTERM) == 0) {
        printf("Process with PID %d terminated successfully.\n", pid);
        return 0;
    } else {
        fprintf(stderr, "Error terminating process with PID %d: %s\n", pid, strerror(errno));
        return 1;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Please provide a process ID as a command-line argument.\n");
        return 1;
    }

    pid_t pid = atoi(argv[1]);  // Convert string to integer
    if (pid == 0 && strcmp(argv[1], "0") != 0) {  // Check for invalid input like non-numeric strings
        fprintf(stderr, "Invalid process ID: %s\n", argv[1]);
        return 1;
    }

    terminateProcess(pid);


    // Test cases (replace with actual PIDs)
    terminateProcess(1234);
    terminateProcess(5678);
    terminateProcess(9012);
    terminateProcess(3456);
    terminateProcess(7890);

    return 0;
}