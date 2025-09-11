#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binarySearch(int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int main() {
    int testCases[] = {10, 100, 1000, 10000, 100000};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    FILE *tempFile = tmpfile(); // Create a temporary file
    if (tempFile == NULL) {
        perror("Error creating temporary file");
        return 1;
    }

    for (int i = 0; i < numTestCases; i++) {
        int size = testCases[i];
        int *arr = (int *)malloc(size * sizeof(int));
        if (arr == NULL) {
            perror("Memory allocation failed");
            fclose(tempFile); // Close the file if malloc fails
            return 1;
        }

        // Fill array with sorted random numbers.
        for (int j = 0; j < size; j++) {
            arr[j] = j; // simplified for sorted data
        }

        int target = rand() % (size*2); // simplified

        clock_t startTime = clock();
        binarySearch(arr, size, target);
        clock_t endTime = clock();

        double executionTime = (double)(endTime - startTime) * 1000000/ CLOCKS_PER_SEC;  //ns


        fprintf(tempFile, "Array size: %d, Execution time: %.0lf ns\n", size, executionTime);

        free(arr); // Free the allocated memory
    }

    // Rewind the file pointer to the beginning to read the contents (optional).
    rewind(tempFile);
    char ch;
    while ((ch = fgetc(tempFile)) != EOF) {
        putchar(ch);
    }

    fclose(tempFile); // Close and delete the temporary file
    return 0;
}