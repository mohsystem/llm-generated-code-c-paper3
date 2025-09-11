#include <stdio.h>
#include <time.h>

int binarySearch(int array[], int size, int target) {
    int low = 0, high = size - 1;
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
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(array) / sizeof(array[0]);
    int targets[] = {5, 1, 10, 0, 8};

    FILE *file = fopen("temp_c.txt", "w");

    for (int i = 0; i < 5; i++) {
        clock_t start = clock();
        int result = binarySearch(array, size, targets[i]);
        clock_t end = clock();
        double duration = (double)(end - start) * 1000000000 / CLOCKS_PER_SEC;

        fprintf(file, "Target: %d, Result: %d, Duration: %.0f ns\n", targets[i], result, duration);
    }

    fclose(file);
    return 0;
}