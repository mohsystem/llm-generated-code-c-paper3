#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void terminate_process(int pid) {
    if (kill(pid, SIGTERM) != 0) {
        perror("Failed to terminate process");
        exit(EXIT_FAILURE);
    }
    printf("Process %d terminated successfully.\n", pid);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PID>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int pid = atoi(argv[1]);
    terminate_process(pid);
    return EXIT_SUCCESS;
}