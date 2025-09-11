#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void terminate_process(int pid) {
    if (kill(pid, SIGTERM) == 0) {
        printf("Terminated process with PID: %d\n", pid);
    } else {
        printf("Failed to terminate process with PID: %d\n", pid);
    }
}

int main() {
    int test_pids[] = {1234, 5678, 9101, 1121, 3141}; // Replace with actual PIDs to test
    for (int i = 0; i < 5; i++) {
        terminate_process(test_pids[i]);
    }
    return 0;
}