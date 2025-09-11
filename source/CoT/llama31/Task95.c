#include <stdio.h>
#include <time.h>

void printProcessorTime() {
    clock_t currentTime = clock();
    double seconds = (double) currentTime / CLOCKS_PER_SEC;
    printf("Current processor time in seconds: %f\n", seconds);
}

int main() {
    for (int i = 0; i < 5; i++) {
        printProcessorTime();
    }
    return 0;
}