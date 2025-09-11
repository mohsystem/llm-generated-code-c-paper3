
#include <stdio.h>
#include <time.h>
#include <math.h>

clock_t getProcessorTime() {
    return clock() / CLOCKS_PER_SEC;
}

int main() {
    // Test cases
    for(int i = 0; i < 5; i++) {
        printf("Test case %d: %lu seconds\\n", i+1, getProcessorTime());
        // Do some computation to see time difference
        for(int j = 0; j < 1000000; j++) {
            sqrt(j);
        }
    }
    return 0;
}
