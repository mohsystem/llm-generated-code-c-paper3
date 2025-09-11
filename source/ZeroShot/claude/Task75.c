
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <signal.h>
#endif

int terminate_process(int pid) {
    #ifdef _WIN32
        HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
        if (hProcess == NULL) {
            return 0;
        }
        int result = TerminateProcess(hProcess, 1);
        CloseHandle(hProcess);
        return result;
    #else
        return (kill(pid, SIGTERM) == 0);
    #endif
}

int main() {
    // Test cases
    int test_pids[] = {1234, 5678, 9012, 3456, 7890};
    int i;
    
    for(i = 0; i < 5; i++) {
        printf("Attempting to terminate process with PID: %d\\n", test_pids[i]);
        int result = terminate_process(test_pids[i]);
        printf("Process termination %s\\n", result ? "successful" : "failed");
    }
    
    return 0;
}
