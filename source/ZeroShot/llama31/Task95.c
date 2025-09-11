#include <stdio.h>
#include <time.h>

double get_cpu_time() {
    clock_t start, end;
    start = clock();
    // Simulate some work
    for (int i = 0; i < 10000000; i++) {
        i * i;
    }
    end = clock();
    double cpu_time = (double)(end - start) / CLOCKS_PER_SEC;
    return cpu_time;
}

int main() {
    for (int i = 0; i < 5; i++) {
        double cpu_time = get_cpu_time();
        printf("CPU time: %f seconds\n", cpu_time);
    }
    return 0;
}