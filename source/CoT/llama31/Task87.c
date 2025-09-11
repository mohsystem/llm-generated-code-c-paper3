#include <stdio.h>
#include <time.h>

int binarySearch(int array[], int x, int low, int high) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (array[mid] == x)
            return mid;
        if (array[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int main() {
    int array[] = {3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(array) / sizeof(array[0]);

    // Test cases
    int testCases[] = {4, 9, 1, 7, 10};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; ++i) {
        int x = testCases[i];
        struct timespec startTime, endTime;
        clock_gettime(CLOCK_MONOTONIC, &startTime);
        int result = binarySearch(array, x, 0, n - 1);
        clock_gettime(CLOCK_MONOTONIC, &endTime);
        long executionTime = (endTime.tv_sec - startTime.tv_sec) * 1000000000 + (endTime.tv_nsec - startTime.tv_nsec);

        // Write execution time to a temporary file
        FILE *file = fopen("execution_time.txt", "a");
        if (file != NULL) {
            fprintf(file, "Execution time for %d: %ld nanoseconds\n", x, executionTime);
            fclose(file);
        }

        if (result == -1)
            printf("Element %d is not present in array\n", x);
        else
            printf("Element %d is present at index %d\n", x, result);
    }

    return 0;
}