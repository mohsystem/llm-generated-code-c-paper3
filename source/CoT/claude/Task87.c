
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void write_execution_time(double time) {
    FILE *file = fopen("execution_time.txt", "w");
    if (file != NULL) {
        fprintf(file, "Execution time: %f seconds", time);
        fclose(file);
    } else {
        fprintf(stderr, "Error opening file for writing\\n");
    }
}

void print_array(int arr[], int size) {
    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\\n");
}

int main() {
    // Test cases
    int test_arrays[][8] = {
        {1, 3, 5, 7, 9, 11, 13, 15},
        {2, 4, 6, 8, 10, 12, 14},
        {1, 2, 3, 4, 5},
        {10, 20, 30, 40, 50, 60},
        {1}
    };
    int targets[] = {7, 12, 1, 45, 1};
    int sizes[] = {8, 7, 5, 6, 1};

    for (int i = 0; i < 5; i++) {
        clock_t start = clock();
        int result = binary_search(test_arrays[i], sizes[i], targets[i]);
        clock_t end = clock();
        
        printf("Test case %d:\\n", i+1);
        print_array(test_arrays[i], sizes[i]);
        printf("Target: %d\\n", targets[i]);
        printf("Result: %d\\n", result);
        
        double cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
        write_execution_time(cpu_time);
        printf("Execution time written to file\\n\\n");
    }

    return 0;
}
