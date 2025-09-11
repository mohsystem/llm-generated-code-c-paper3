#include <stdio.h>
#include <time.h>

double getCurrentProcessorTime() {
    return (double)clock() / CLOCKS_PER_SEC;
}

int main() {
    printf("Test case 1: %f\n", getCurrentProcessorTime());
    printf("Test case 2: %f\n", getCurrentProcessorTime());
    printf("Test case 3: %f\n", getCurrentProcessorTime());
    printf("Test case 4: %f\n", getCurrentProcessorTime());
    printf("Test case 5: %f\n", getCurrentProcessorTime());
    return 0;
}