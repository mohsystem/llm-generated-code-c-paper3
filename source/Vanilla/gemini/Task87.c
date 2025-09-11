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
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

int main() {
    int testCases[] = {10, 100, 1000, 10000, 100000};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        int size = testCases[i];
        int *arr = (int *)malloc(size * sizeof(int));

        for (int j = 0; j < size; j++) {
            arr[j] = rand() % (size * 2); 
        }

        // Sort the array (binary search requires a sorted array)
        for(int k=0; k < size-1; k++){
            for(int l=0; l < size-k-1; l++){
                if(arr[l] > arr[l+1]){
                    int temp = arr[l];
                    arr[l] = arr[l+1];
                    arr[l+1] = temp;
                }
            }
        }



        int target = rand() % (size * 2);

        clock_t startTime = clock();
        binarySearch(arr, size, target);
        clock_t endTime = clock();
        double executionTime = (double)(endTime - startTime) * 1000000000/ CLOCKS_PER_SEC;


        FILE *fp = fopen("temp.txt", "a");
        if (fp == NULL) {
            perror("Error opening file");
            return 1;
        }
        fprintf(fp, "Execution time for array size %d: %.0f nanoseconds\n", size, executionTime);
        fclose(fp);

        free(arr);
    }

    return 0;
}