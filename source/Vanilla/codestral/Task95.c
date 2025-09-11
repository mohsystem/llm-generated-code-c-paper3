#include <stdio.h>
#include <time.h>
#include <math.h>

double getProcessorTime() {
    clock_t startTime = clock();
    // Perform some work to consume processor time
    for (int i = 0; i < 1000000; i++) {
        sqrt(i);
    }
    clock_t endTime = clock();
    return (double)(endTime - startTime) / CLOCKS_PER_SEC;
}

int main() {
    printf("%f\n", getProcessorTime());
    return 0;
}