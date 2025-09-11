#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binarySearch(int array[], int size, int target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (array[mid] == target) {
            return mid;
        }
        if (array[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

void logExecutionTime(long executionTime) {
    FILE *tempFile = tmpfile();
    if (tempFile != NULL) {
        fprintf(tempFile, "Execution time: %ld nanoseconds\n", executionTime);
        fclose(tempFile);
    }
}

int main() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(array) / sizeof(array[0]);

    // Test cases
    int testCases[] = {1, 5, 10, -1, 11};
    for (int i = 0; i < 5; i++) {
        int target = testCases[i];
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        int result = binarySearch(array, size, target);
        clock_gettime(CLOCK_MONOTONIC, &end);

        long executionTime = (end.tv_sec - start.tv_sec) * 1000000000L + (end.tv_nsec - start.tv_nsec);
        printf("Target: %d Index: %d\n", target, result);
        logExecutionTime(executionTime);
    }

    return 0;
}