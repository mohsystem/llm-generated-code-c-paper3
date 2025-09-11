#include <stdio.h>
#include <stdlib.h>

void terminateProcess(int pid) {
    char command[20];
    sprintf(command, "kill %d", pid);
    system(command);
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        int pid = atoi(argv[1]);
        terminateProcess(pid);
    } else {
        printf("Please provide a process ID as a command line argument.\n");
    }
    return 0;
}