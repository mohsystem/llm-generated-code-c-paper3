#include <stdio.h>
#include <time.h>

int binarySearch(int array[], int target, int size) {
    int low = 0;
    int high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (array[mid] == target) {
            return mid;
        } else if (array[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int main() {
    int array[] = {3, 4, 5, 6, 7, 8, 9};
    int targets[] = {4, 6, 8, 10, 5};
    int size = sizeof(array) / sizeof(array[0]);

    FILE *file = fopen("execution_time.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    for (int target : targets) {
        time_t start_time = time(NULL);
        clock_t start_clock = clock();
        int result = binarySearch(array, target, size);
        time_t end_time = time(NULL);
        clock_t end_clock = clock();
        double execution_time = (double)(end_clock - start_clock) / CLOCKS_PER_SEC;

        fprintf(file, "Target: %d, Result: %d, Execution Time: %f seconds\n", target, result, execution_time);

        if (result != -1) {
            printf("Element %d is present at index %d\n", target, result);
        } else {
            printf("Element %d not found\n", target);
        }
    }

    fclose(file);
    return 0;
}