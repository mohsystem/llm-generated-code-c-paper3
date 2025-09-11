
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int binarySearch(int arr[], int size, int target) {
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
    char temp_filename[L_tmpnam];
    tmpnam(temp_filename);
    
    FILE* fp = fopen(temp_filename, "w");
    if (fp != NULL) {
        fprintf(fp, "Execution time: %ld clock ticks", time);
        fclose(fp);
    }
}

int main() {
    // Test cases
    int arrays[][8] = {
        {1, 3, 5, 7, 9, 11},
        {2, 4, 6, 8, 10},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {10, 20, 30, 40, 50},
        {1}
    };
    int sizes[] = {6, 5, 8, 5, 1};
    int targets[] = {7, 10, 1, 25, 1};
    
    for (int i = 0; i < 5; i++) {
        clock_t start = clock();
        int result = binarySearch(arrays[i], sizes[i], targets[i]);
        clock_t end = clock();
        
        printf("Test case %d:\\n", i+1);
        printf("Array: ");
        for (int j = 0; j < sizes[i]; j++) {
            printf("%d ", arrays[i][j]);
        }
        printf("\\nTarget: %d\\n", targets[i]);
        printf("Result index: %d\\n\\n", result);
        
        writeExecutionTime(end - start);
    }
    
    return 0;
}
