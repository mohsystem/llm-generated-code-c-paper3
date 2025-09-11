
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <limits.h>

int terminate_process(int pid) {
    if (pid <= 0) {
        fprintf(stderr, "Invalid PID provided\\n");
        return 0;
    }
    
    #ifdef _WIN32
        char command[32];
        snprintf(command, sizeof(command), "taskkill /F /PID %d", pid);
        int result = system(command);
        return result == 0;
    #else
        if (kill(pid, SIGTERM) == 0) {
            return 1;
        } else {
            switch (errno) {
                case ESRCH:
                    fprintf(stderr, "Process not found\\n");
                    break;
                case EPERM:
                    fprintf(stderr, "Permission denied\\n");
                    break;
                default:
                    fprintf(stderr, "Error terminating process\\n");
            }
            return 0;
        }
    #endif
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pid>\\n", argv[0]);
        return 1;
    }

    char* endptr;
    errno = 0;
    long pid = strtol(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\\0' || pid <= 0 || pid > INT_MAX) {
        fprintf(stderr, "Invalid PID format. Please provide a valid number\\n");
        return 1;
    }

    int success = terminate_process((int)pid);
    printf("%s\\n", success ? "Process terminated successfully" : "Failed to terminate process");
    return success ? 0 : 1;
}
