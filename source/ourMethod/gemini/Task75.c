#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int terminate_process(int pid) {
     if (kill(pid, SIGTERM) != 0) {
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        return 1;
    }

    int pid = atoi(argv[1]);
    if (pid <= 0) { //check pid is valid integer 
        fprintf(stderr, "Invalid PID: %s\n", argv[1]);
        return 1;
    }

    if (terminate_process(pid) == 0){
        printf("Process with PID %d terminated.\n", pid);
        return 0;
    } else {
        fprintf(stderr, "Error terminating process with PID %d: %s\n", pid, strerror(errno));
        return 1;
    }

    return 0;
}