#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binarySearch(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        }

        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

int main() {
    int testCases[] = {5, 10, 100, 1000, 10000};

    for (int i = 0; i < sizeof(testCases) / sizeof(testCases[0]); i++) {
        int n = testCases[i];
        int *arr = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            arr[j] = j * 2;
        }

        int target = rand() % (n*2); // simpler random generation for C

        clock_t start = clock();
        int result = binarySearch(arr, n, target);
        clock_t end = clock();

        double duration = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000000.0; // Nanoseconds

        char filename[50];
        snprintf(filename, sizeof(filename), "binary_search_timing_%d.txt", n);
        FILE *tempFile = fopen(filename, "w");
        fprintf(tempFile, "%.0lf", duration); // write as integer to match other languages
        fclose(tempFile);

        printf("Test case with %d elements, Target:%d , Result index: %d, Time:%.0lfns, Output file: %s\n", n, target, result, duration, filename);

        free(arr);
    }

    return 0;
}