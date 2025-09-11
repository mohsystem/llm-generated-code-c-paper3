#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binarySearch(int array[], int size, int target) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (array[mid] == target) {
            return mid;
        } else if (array[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

void writeExecutionTimeToFile(long executionTime) {
    FILE *file = fopen("execution_time_c.txt", "w");
    if (file != NULL) {
        fprintf(file, "Execution Time: %ld ns", executionTime);
        fclose(file);
    }
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(array) / sizeof(array[0]);
    int testCases[] = {5, 1, 10, 11, -1};

    qsort(array, size, sizeof(int), compare); // Ensure the array is sorted for binary search

    for (int i = 0; i < 5; i++) {
        int target = testCases[i];
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        int result = binarySearch(array, size, target);
        clock_gettime(CLOCK_MONOTONIC, &end);
        long executionTime = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);

        printf("Target: %d, Result: %d\n", target, result);
        writeExecutionTimeToFile(executionTime);
    }

    return 0;
}