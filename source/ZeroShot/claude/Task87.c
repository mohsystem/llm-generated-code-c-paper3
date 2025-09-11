
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int binary_search(int arr[], int size, int target) {
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
    FILE *fp = fopen("execution_time.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\\n");
        return 1;
    }
    
    // Test cases
    int test_arrays[][10] = {
        {1, 3, 5, 7, 9, 11, 13, 15},
        {2, 4, 6, 8, 10, 12, 14, 16, 18},
        {1, 2, 3, 4, 5},
        {10, 20, 30, 40, 50, 60},
        {1, 3, 5, 7, 9, 11, 13, 15, 17, 19}
    };
    
    int array_sizes[] = {8, 9, 5, 6, 10};
    int search_values[] = {7, 14, 5, 30, 20};
    
    for (int i = 0; i < 5; i++) {
        clock_t start = clock();
        int result = binary_search(test_arrays[i], array_sizes[i], search_values[i]);
        clock_t end = clock();
        double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC * 1e9; // Convert to nanoseconds
        
        fprintf(fp, "Test case %d:\\n", i+1);
        fprintf(fp, "Array: ");
        for (int j = 0; j < array_sizes[i]; j++) {
            fprintf(fp, "%d ", test_arrays[i][j]);
        }
        fprintf(fp, "\\nSearch value: %d\\n", search_values[i]);
        fprintf(fp, "Result index: %d\\n", result);
        fprintf(fp, "Execution time: %.0f nanoseconds\\n\\n", cpu_time_used);
    }
    
    fclose(fp);
    return 0;
}
