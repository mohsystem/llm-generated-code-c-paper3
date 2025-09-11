#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void kill_process(int pid) {
    char command[50];
    sprintf(command, "kill %d", pid);
    if (system(command) != 0) {
        fprintf(stderr, "Error terminating process\n");
        exit(1);
    }
    printf("Process %d terminated.\n", pid);
}

int main(int argc, char* argv[]) {
    // Test cases
    int testCases[] = {1234, 5678, 9012};
    for (int i = 0; i < 3; i++) {
        kill_process(testCases[i]);
    }
    return 0;
}