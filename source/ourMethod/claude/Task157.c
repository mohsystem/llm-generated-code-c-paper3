
#include <stdio.h>
#include <stdlib.h>

int* allocateAndDeallocate(int size) {
    if (size <= 0) {
        return NULL;
    }
    
    // Allocate memory
    int* array = (int*)malloc(size * sizeof(int));
    if (array == NULL) {
        return NULL;
    }
    
    // Initialize array
    for (int i = 0; i < size; i++) {
        array[i] = i;
    }
    
    return array;
}

void deallocateMemory(int* ptr) {
    free(ptr);
}

int main() {
    // Test Case 1: Size 5
    printf("Test Case 1: Size 5\\n");
    int* result1 = allocateAndDeallocate(5);
    if (result1 != NULL) {
        for (int i = 0; i < 5; i++) {
            printf("%d ", result1[i]);
        }
        printf("\\n");
        deallocateMemory(result1);
    }
    
    // Test Case 2: Size 0
    printf("\\nTest Case 2: Size 0\\n");
    int* result2 = allocateAndDeallocate(0);
    printf("%s\\n", result2 == NULL ? "Null returned" : "Array created");
    
    // Test Case 3: Size 10
    printf("\\nTest Case 3: Size 10\\n");
    int* result3 = allocateAndDeallocate(10);
    if (result3 != NULL) {
        for (int i = 0; i < 10; i++) {
            printf("%d ", result3[i]);
        }
        printf("\\n");
        deallocateMemory(result3);
    }
    
    // Test Case 4: Size -5
    printf("\\nTest Case 4: Size -5\\n");
    int* result4 = allocateAndDeallocate(-5);
    printf("%s\\n", result4 == NULL ? "Null returned" : "Array created");
    
    // Test Case 5: Size 3
    printf("\\nTest Case 5: Size 3\\n");
    int* result5 = allocateAndDeallocate(3);
    if (result5 != NULL) {
        for (int i = 0; i < 3; i++) {
            printf("%d ", result5[i]);
        }
        printf("\\n");
        deallocateMemory(result5);
    }
    
    return 0;
}
