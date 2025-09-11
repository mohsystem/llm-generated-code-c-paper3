
#include <stdio.h>
#include <stdlib.h>

int* removeSmallest(const int* numbers, int length, int* resultLength) {
    if (length == 0) {
        *resultLength = 0;
        return NULL;
    }
    
    int minIndex = 0;
    for (int i = 1; i < length; i++) {
        if (numbers[i] < numbers[minIndex]) {
            minIndex = i;
        }
    }
    
    *resultLength = length - 1;
    int* result = (int*)malloc((*resultLength) * sizeof(int));
    
    for (int i = 0, j = 0; i < length; i++) {
        if (i != minIndex) {
            result[j++] = numbers[i];
        }
    }
    
    return result;
}

int main() {
    // Test case 1
    printf("Test case 1:\\n");
    int arr1[] = {1,2,3,4,5};
    int resultLength1;
    int* result1 = removeSmallest(arr1, 5, &resultLength1);
    for(int i = 0; i < resultLength1; i++) printf("%d ", result1[i]);
    free(result1);
    
    // Test case 2
    printf("\\nTest case 2:\\n");
    int arr2[] = {5,3,2,1,4};
    int resultLength2;
    int* result2 = removeSmallest(arr2, 5, &resultLength2);
    for(int i = 0; i < resultLength2; i++) printf("%d ", result2[i]);
    free(result2);
    
    // Test case 3
    printf("\\nTest case 3:\\n");
    int arr3[] = {2,2,1,2,1};
    int resultLength3;
    int* result3 = removeSmallest(arr3, 5, &resultLength3);
    for(int i = 0; i < resultLength3; i++) printf("%d ", result3[i]);
    free(result3);
    
    // Test case 4
    printf("\\nTest case 4:\\n");
    int resultLength4;
    int* result4 = removeSmallest(NULL, 0, &resultLength4);
    if(result4 == NULL) printf("Empty array");
    free(result4);
    
    // Test case 5
    printf("\\nTest case 5:\\n");
    int arr5[] = {1};
    int resultLength5;
    int* result5 = removeSmallest(arr5, 1, &resultLength5);
    for(int i = 0; i < resultLength5; i++) printf("%d ", result5[i]);
    free(result5);
    
    return 0;
}
