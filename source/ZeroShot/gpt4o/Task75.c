#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

int terminateProcess(int pid) {
    if (pid <= 0) {
        return 0;
    }
    int result;
#ifdef _WIN32
    char command[256];
    sprintf(command, "taskkill /PID %d /F", pid);
    result = system(command);
#else
    char command[256];
    sprintf(command, "kill -9 %d", pid);
    result = system(command);
#endif
    return (result == 0);
}

int main() {
    int testPIDs[] = {1234, 5678, 9101, 1121, 3141};
    for (int i = 0; i < 5; i++) {
        int result = terminateProcess(testPIDs[i]);
        printf("Terminate process %d: %s\n", testPIDs[i], result ? "true" : "false");
    }
    return 0;
}