#include <stdio.h>
#include <time.h>

double getProcessorTime() {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    clock_gettime(CLOCK_MONOTONIC, &end);
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

int main() {
    printf("Processor time: %.6f seconds\n", getProcessorTime());
    return 0;
}