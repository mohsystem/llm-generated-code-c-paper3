#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
#include <process.h>
#endif

int terminateProcess(int pid) {
    #ifdef _WIN32
        char command[256];
        snprintf(command, sizeof(command), "taskkill /F /PID %d", pid);
        return system(command);
    #else
        return kill(pid, SIGTERM);
    #endif
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        return 1;
    }

    int pid = atoi(argv[1]);
    if (pid <= 0) {
         fprintf(stderr, "Invalid PID.\n");
        return 1;
    }


    int result = terminateProcess(pid);

    if (result == 0) {
        printf("Process terminated successfully.\n");
    } else {
        fprintf(stderr, "Error terminating process: %s\n", strerror(errno)); // Use strerror for error details
        return 1;
    }

    return 0;
}