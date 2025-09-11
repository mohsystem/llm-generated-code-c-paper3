#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binarySearch(int arr[], int size, int key) {
    int low = 0;
    int high = size - 1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] == key)
            return mid;
        
        if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    
    return -1;
}

void logExecutionTime(long time_ns) {
    FILE *file = fopen("execution_time.txt", "w");
    if (file != NULL) {
        fprintf(file, "Execution Time: %ld ns\n", time_ns);
        fclose(file);
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int testKeys[] = {5, 1, 10, 11, 0};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    for (int i = 0; i < 5; i++) {
        int key = testKeys[i];
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        int result = binarySearch(arr, size, key);
        clock_gettime(CLOCK_MONOTONIC, &end);
        long time_ns = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
        logExecutionTime(time_ns);
        printf("Key: %d Result: %d\n", key, result);
    }
    
    return 0;
}