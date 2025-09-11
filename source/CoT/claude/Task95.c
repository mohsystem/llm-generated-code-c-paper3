
#include <stdio.h>
#include <time.h>
#include <unistd.h>

double get_processor_time() {
    clock_t time = clock();
    return ((double)time) / CLOCKS_PER_SEC;
}

int main() {
    // Test cases
    for(int i = 0; i < 5; i++) {
        printf("Test case %d: %f seconds\\n", i+1, get_processor_time());
        sleep(1); // Wait 1 second between tests
    }
    return 0;
}
