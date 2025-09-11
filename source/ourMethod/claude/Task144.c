
#include <stdio.h>
#include <stdlib.h>

struct Result {
    int* array;
    int size;
};

struct Result mergeSortedArrays(const int* arr1, int size1, const int* arr2, int size2) {
    struct Result result;
    
    // Input validation
    if (arr1 == NULL || arr2 == NULL) {
        result.array = NULL;
        result.size = 0;
        return result;
    }
    
    // Allocate memory for result array
    result.array = (int*)malloc((size1 + size2) * sizeof(int));
    if (result.array == NULL) {
        result.size = 0;
        return result;
    }
    result.size = size1 + size2;
    
    int i = 0, j = 0, k = 0;
    
    // Merge arrays while comparing elements
    while (i < size1 && j < size2) {
        if (arr1[i] <= arr2[j]) {
            result.array[k++] = arr1[i++];
        } else {
            result.array[k++] = arr2[j++];
        }
    }
    
    // Copy remaining elements from arr1, if any
    while (i < size1) {
        result.array[k++] = arr1[i++];
    }
    
    // Copy remaining elements from arr2, if any
    while (j < size2) {
        result.array[k++] = arr2[j++];
    }
    
    return result;
}

void printArray(const int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\\n");
}

int main() {
    // Test case 1
    int test1_1[] = {1, 3, 5};
    int test1_2[] = {2, 4, 6};
    struct Result result1 = mergeSortedArrays(test1_1, 3, test1_2, 3);
    printf("Test 1: ");
    printArray(result1.array, result1.size);
    free(result1.array);

    // Test case 2
    int test2_1[] = {1, 2, 3, 4};
    int test2_2[] = {5, 6, 7, 8};
    struct Result result2 = mergeSortedArrays(test2_1, 4, test2_2, 4);
    printf("Test 2: ");
    printArray(result2.array, result2.size);
    free(result2.array);

    // Test case 3
    int test3_2[] = {1, 2, 3};
    struct Result result3 = mergeSortedArrays(NULL, 0, test3_2, 3);
    printf("Test 3: ");
    if (result3.array == NULL) {
        printf("[]\\n");
    } else {
        printArray(result3.array, result3.size);
        free(result3.array);
    }

    // Test case 4
    int test4_1[] = {1, 1, 1};
    int test4_2[] = {1, 1, 1};
    struct Result result4 = mergeSortedArrays(test4_1, 3, test4_2, 3);
    printf("Test 4: ");
    printArray(result4.array, result4.size);
    free(result4.array);

    // Test case 5
    int test5_2[] = {1, 2, 3};
    struct Result result5 = mergeSortedArrays(NULL, 0, test5_2, 3);
    printf("Test 5: ");
    if (result5.array == NULL) {
        printf("[]\\n");
    } else {
        printArray(result5.array, result5.size);
        free(result5.array);
    }

    return 0;
}
