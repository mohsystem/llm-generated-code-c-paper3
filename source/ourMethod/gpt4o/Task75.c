#include <stdio.h>
#include <signal.h>
#include <stdbool.h>

bool terminateProcess(int pid) {
    if (pid <= 0) return false; // Invalid PID
    if (kill(pid, SIGKILL) == 0) {
        return true;
    }
    return false;
}

int main() {
    int testPIDs[] = {1234, 5678, 91011, 1213, 1415};
    int numTests = sizeof(testPIDs) / sizeof(testPIDs[0]);
    for (int i = 0; i < numTests; i++) {
        int pid = testPIDs[i];
        bool result = terminateProcess(pid);
        printf("Terminating PID %d: %s\n", pid, result ? "Success" : "Failed");
    }
    return 0;
}