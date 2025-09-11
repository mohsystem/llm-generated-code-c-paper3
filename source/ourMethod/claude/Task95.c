
#include <stdio.h>
#include <time.h>
#include <unistd.h>

clock_t get_current_processor_time() {
    return clock() / CLOCKS_PER_SEC;  // Convert clock ticks to seconds
}

int main() {
    // Test cases
    for(int i = 0; i < 5; i++) {
        printf("Current processor time in seconds: %ld\\n", get_current_processor_time());
        sleep(1); // Wait 1 second between readings
    }
    return 0;
}
