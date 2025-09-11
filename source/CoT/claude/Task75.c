
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int terminate_process(int pid) {
    if (pid <= 0) {
        return 0;
    }
    
    #ifdef _WIN32
        char command[100];
        snprintf(command, sizeof(command), "taskkill /F /PID %d", pid);
        return system(command) == 0;
    #else
        return kill(pid, SIGTERM) == 0;
    #endif
}

int main() {
    // Test cases
    int test_pids[] = {1234, 5678, 9012, 3456, 7890};
    int num_tests = 5;
    
    for(int i = 0; i < num_tests; i++) {
        printf("Attempting to terminate process with PID: %d\\n", test_pids[i]);
        int result = terminate_process(test_pids[i]);
        printf("Process termination %s\\n", result ? "successful" : "failed");
    }
    
    return 0;
}
