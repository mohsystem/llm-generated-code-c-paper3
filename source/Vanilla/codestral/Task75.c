// C code
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void terminateProcess(int pid) {
    if (kill(pid, SIGTERM) == -1) {
        perror("Could not terminate process");
    } else {
        printf("Process successfully terminated.\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Please provide exactly one argument: the PID.\n");
        return 1;
    }
    int pid = atoi(argv[1]);
    terminateProcess(pid);
    return 0;
}