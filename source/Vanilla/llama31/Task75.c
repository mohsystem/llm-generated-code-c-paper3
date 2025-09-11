#include <stdio.h>
#include <stdlib.h>

void terminateProcess(int pid) {
    char command[50];
    sprintf(command, "kill %d", pid);
    system(command);
    printf("Process %d terminated.\n", pid);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: ./task75 <PID>\n");
        return 1;
    }
    int pid = atoi(argv[1]);
    terminateProcess(pid);
    return 0;
}