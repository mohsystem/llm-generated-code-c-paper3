#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int terminateProcess(int pid) {
    #ifdef _WIN32
        char command[50];
        sprintf(command, "taskkill /F /PID %d", pid);
        return system(command);
    #else
        return kill(pid, SIGTERM);
    #endif
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Please provide PID as command line argument.\n");
        return 1;
    }

    int pid;
    if (sscanf(argv[1], "%d", &pid) != 1) {
        fprintf(stderr, "Invalid PID format.\n");
        return 1;
    }
    

    int result = terminateProcess(pid);
    if (result == 0) {
        printf("Process with PID %d terminated successfully (or doesn't exist).\n", pid);
    } else {
       fprintf(stderr, "Failed to terminate process with PID %d\n", pid);
    }



    terminateProcess(1234); // Test case 1
    terminateProcess(5678); // Test case 2
    terminateProcess(9012); // Test case 3
    terminateProcess(3456); // Test case 4
    terminateProcess(7890); // Test case 5


    return 0;
}