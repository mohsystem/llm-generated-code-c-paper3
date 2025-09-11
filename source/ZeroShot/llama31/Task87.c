#include <stdio.h>
#include <time.h>

int binarySearch(int array[], int x, int size) {
    int low = 0;
    int high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (array[mid] == x) {
            return mid;
        } else if (array[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int main() {
    int array[] = {3, 4, 5, 6, 7, 8, 9};
    int testCases[] = {4, 6, 9, 10, 3};
    int size = sizeof(array) / sizeof(array[0]);

    FILE *file = fopen("execution_time.txt", "w");

    for (int i = 0; i < 5; ++i) {
        clock_t start = clock();
        int result = binarySearch(array, testCases[i], size);
        clock_t end = clock();
        double executionTime = (double)(end - start) / CLOCKS_PER_SEC;

        fprintf(file, "Execution time for searching %d: %.6f seconds\n", testCases[i], executionTime);
        if (result != -1) {
            fprintf(file, "Element %d found at index %d\n", testCases[i], result);
        } else {
            fprintf(file, "Element %d not found\n", testCases[i]);
        }
    }

    fclose(file);
    return 0;
}