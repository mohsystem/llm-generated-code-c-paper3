#include <stdio.h>
#include <time.h>
#include <unistd.h>

// Note: True processor time is platform-specific and difficult to get portably in C.
// This provides a substitute using clock(), which measures CPU time.
double getProcessorTimeInSeconds() {
    return (double)clock() / CLOCKS_PER_SEC;
}


int main() {
    for (int i = 0; i < 5; i++) {
        printf("Processor time (seconds): %.6f\n", getProcessorTimeInSeconds());
        sleep(1); // Wait 1 second
    }
    return 0;
}