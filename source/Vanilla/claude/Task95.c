
#include <stdio.h>
#include <time.h>
#include <math.h>

double getProcessorTime() {
    clock_t time = clock();
    return ((double)time) / CLOCKS_PER_SEC;
}

int main() {
    // Test cases
    for(int i = 0; i < 5; i++) {
        printf("Test case %d: %f seconds\\n", i+1, getProcessorTime());
        // Do some computation to show different times
        for(int j = 0; j < i*1000000; j++) {
            sqrt(j);
        }
    }
    return 0;
}
