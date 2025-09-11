#include <stdio.h>
#include <time.h>

double getCurrentProcessorTimeInSeconds() {
    return (double)clock() / CLOCKS_PER_SEC;
}

int main() {
    printf("%f\n", getCurrentProcessorTimeInSeconds());
    printf("%f\n", getCurrentProcessorTimeInSeconds());
    printf("%f\n", getCurrentProcessorTimeInSeconds());
    printf("%f\n", getCurrentProcessorTimeInSeconds());
    printf("%f\n", getCurrentProcessorTimeInSeconds());
    return 0;
}