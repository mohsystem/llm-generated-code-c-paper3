#include <stdio.h>
#include <time.h>

double getProcessorTimeInSeconds() {
    clock_t start_time = clock();
    return (double)start_time / CLOCKS_PER_SEC;
}

int main() {
    printf("Test case 1: %f\n", getProcessorTimeInSeconds());
    printf("Test case 2: %f\n", getProcessorTimeInSeconds());
    printf("Test case 3: %f\n", getProcessorTimeInSeconds());
    printf("Test case 4: %f\n", getProcessorTimeInSeconds());
    printf("Test case 5: %f\n", getProcessorTimeInSeconds());
    return 0;
}