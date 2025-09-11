
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int binarySearch(const int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target)
            return mid;
            
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

void writeExecutionTime(clock_t time) {
    FILE *file = fopen("execution_time.txt", "w");
    if (file != NULL) {
        fprintf(file, "Execution time: %ld clock ticks", time);
        fclose(file);
    } else {
        fprintf(stderr, "Error opening file for writing\\n");
    }
}

int main() {
    // Test cases
    int testArrays[][8] = {
        {1, 3, 5, 7, 9, 11},
        {2, 4, 6, 8, 10, 12, 14},
        {1, 2, 3, 4, 5},
        {10, 20, 30, 40, 50, 60},
        {1, 3, 5, 7, 9, 11, 13, 15}
    };
    int testSizes[] = {6, 7, 5, 6, 8};
    int targets[] = {7, 8, 1, 60, 10};
    
    for(int i = 0; i < 5; i++) {
        clock_t startTime = clock();
        int result = binarySearch(testArrays[i], testSizes[i], targets[i]);
        clock_t endTime = clock();
        
        printf("Test case %d:\\n", i+1);
        printf("Target: %d\\n", targets[i]);
        printf("Result index: %d\\n", result);
        writeExecutionTime(endTime - startTime);
        printf("\\n");
    }
    
    return 0;
}
