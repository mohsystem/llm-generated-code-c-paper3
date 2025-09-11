
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
    for(int i = 0; i < size; i++) {
        array[i] = i + 1;
    }
    
    return array;
}

int main() {
    // Test cases
    int testSizes[] = {5, 10, 0, -5, 3};
    int numTests = 5;
    
    for(int i = 0; i < numTests; i++) {
        int size = testSizes[i];
        printf("Test case with size: %d\\n", size);
        
        int* result = allocateAndDeallocate(size);
        
        if(result != NULL) {
            printf("Allocated array: ");
            for(int j = 0; j < size; j++) {
                printf("%d ", result[j]);
            }
            printf("\\n");
            
            // Deallocate memory
            free(result);
            printf("Memory deallocated\\n");
        } else {
            printf("Failed to allocate memory or invalid size\\n");
        }
        printf("\\n");
    }
    
    return 0;
}
