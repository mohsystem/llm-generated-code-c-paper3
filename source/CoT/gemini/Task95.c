#include <stdio.h>
#include <time.h>

double getProcessorTimeInSeconds() {
    clock_t start_time = clock();
    return (double)start_time / CLOCKS_PER_SEC;
}

int main() {
    printf("Test 1: %f\n", getProcessorTimeInSeconds());
    printf("Test 2: %f\n", getProcessorTimeInSeconds());
    printf("Test 3: %f\n", getProcessorTimeInSeconds());
    printf("Test 4: %f\n", getProcessorTimeInSeconds());
    printf("Test 5: %f\n", getProcessorTimeInSeconds());
    return 0;
}