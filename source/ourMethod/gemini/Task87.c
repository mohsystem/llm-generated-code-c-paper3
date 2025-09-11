#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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
    int testCases[][6] = {
        {2, 5, 7, 8, 11, 12},
        {2, 5, 7, 8, 11, 12},
        {1, 2, 3, 4, 5, 6},
        {1, 5},
        {} // Empty array
    };
    int targets[] = {12, 13, 4, 1, 5};
    int numTestCases = sizeof(targets) / sizeof(targets[0]);


    for (int i = 0; i < numTestCases; i++) {
        int size = sizeof(testCases[i]) / sizeof(testCases[i][0]);
        if (i == 4) { // special case of empty array
            size = 0;
        }

        int arr[size];
        memcpy(arr, testCases[i], sizeof(testCases[i][0]) * size); // Create a copy for sorting


        //Sort the array (bubble sort for simplicity)
        for(int j=0; j<size-1; j++){
            for(int k=0; k<size-j-1; k++){
                if(arr[k] > arr[k+1]){
                    int temp = arr[k];
                    arr[k] = arr[k+1];
                    arr[k+1] = temp;
                }
            }
        }
        int target = targets[i];


        clock_t start = clock();
        int result = binarySearch(arr, size, target);
        clock_t end = clock();
        double timeElapsed = ((double)(end - start)) / CLOCKS_PER_SEC;

        char tempFileName[100];
        snprintf(tempFileName, sizeof(tempFileName), "binary_search_execution_time_%d.txt", i);

        FILE *tempFile = fopen(tempFileName, "w");
        if (tempFile != NULL) {
            fprintf(tempFile, "Execution time: %f seconds\n", timeElapsed);
            fclose(tempFile);
            printf("Test case %d: Target %d found at index: %d\n", i + 1, target, result);
            printf("Execution time written to: %s\n", tempFileName);
        } else {
            perror("Error creating temporary file");
        }
    }
    return 0;
}