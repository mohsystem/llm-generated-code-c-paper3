#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void terminateProcessC(int pid) {
    if (kill(pid, SIGTERM) == -1) {
        perror("Error");
    }
}

int main() {
    // Test cases
    terminateProcessC(1234);
    terminateProcessC(5678);
    terminateProcessC(9101);
    terminateProcessC(1121);
    terminateProcessC(3141);
    return 0;
}