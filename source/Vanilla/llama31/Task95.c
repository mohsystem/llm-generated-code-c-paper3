#include <stdio.h>
#include <time.h>

double getProcessorTime() {
    return (double)clock() / CLOCKS_PER_SEC;
}

int main() {
    clock_t start_time = clock();
    // Your code here
    clock_t end_time = clock();
    double processor_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Processor time: %f seconds\n", processor_time);

    for (int i = 0; i < 5; i++) {
        start_time = clock();
        // Simulate some work
        for (int j = 0; j < 10000000; j++) {
            rand();
        }
        end_time = clock();
        processor_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("Test Case %d: Processor time: %f seconds\n", i + 1, processor_time);
    }

    return 0;
}