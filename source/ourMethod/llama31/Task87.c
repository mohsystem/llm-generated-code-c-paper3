#include <stdio.h>
#include <time.h>

int binarySearch(int array[], int x, int low, int high) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (x == array[mid]) {
            return mid;
        } else if (x < array[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

int main() {
    int array[] = {3, 4, 5, 6, 7, 8, 9};
    int x = 4;

    clock_t start_time = clock();
    int result = binarySearch(array, x, 0, sizeof(array) / sizeof(array[0]) - 1);
    clock_t end_time = clock();

    FILE *file = fopen("execution_time.txt", "w");
    if (file != NULL) {
        fprintf(file, "Execution time: %f seconds", (double)(end_time - start_time) / CLOCKS_PER_SEC);
        fclose(file);
    } else {
        fprintf(stderr, "Unable to open file");
    }

    if (result != -1) {
        printf("Element is present at index %d\n", result);
    } else {
        printf("Not found\n");
    }

    return 0;
}