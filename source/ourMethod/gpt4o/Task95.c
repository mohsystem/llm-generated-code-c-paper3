#include <stdio.h>
#include <time.h>

double getCurrentProcessorTime() {
    return (double)clock() / CLOCKS_PER_SEC;
}

int main() {
    printf("Processor time: %f seconds\n", getCurrentProcessorTime());
    printf("Processor time: %f seconds\n", getCurrentProcessorTime());
    printf("Processor time: %f seconds\n", getCurrentProcessorTime());
    printf("Processor time: %f seconds\n", getCurrentProcessorTime());
    printf("Processor time: %f seconds\n", getCurrentProcessorTime());
    return 0;
}