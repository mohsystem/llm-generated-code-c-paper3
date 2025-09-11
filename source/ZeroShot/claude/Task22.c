
#include <stdio.h>
#include <stdlib.h>

// Structure to represent mixed type array
typedef struct {
    int value;
    int is_number;  // 1 if number, 0 if string
} Item;

int* filterList(Item* list, int size, int* resultSize) {
    int* result = malloc(size * sizeof(int));
    *resultSize = 0;
    
    for(int i = 0; i < size; i++) {
        if(list[i].is_number) {
            result[*resultSize] = list[i].value;
            (*resultSize)++;
        }
    }
    
    return result;
}

void printArray(int* arr, int size) {
    printf("[");
    for(int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if(i < size - 1) printf(", ");
    }
    printf("]\\n");
}

int main() {
    // Test case 1
    Item test1[] = {{1,1}, {2,1}, {0,0}, {0,0}};  // {1, 2, "a", "b"}
    int size1;
    int* result1 = filterList(test1, 4, &size1);
    printArray(result1, size1);
    free(result1);
    
    // Test case 2
    Item test2[] = {{1,1}, {0,0}, {0,0}, {0,1}, {15,1}};  // {1, "a", "b", 0, 15}
    int size2;
    int* result2 = filterList(test2, 5, &size2);
    printArray(result2, size2);
    free(result2);
    
    // Test case 3
    Item test3[] = {{1,1}, {2,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {123,1}};
    int size3;
    int* result3 = filterList(test3, 8, &size3);
    printArray(result3, size3);
    free(result3);
    
    // Test case 4
    Item test4[] = {{0,0}, {0,0}, {0,1}, {-1,1}, {123,1}};
    int size4;
    int* result4 = filterList(test4, 5, &size4);
    printArray(result4, size4);
    free(result4);
    
    // Test case 5
    Item test5[] = {{1,1}, {2,1}, {3,1}, {4,1}, {5,1}};
    int size5;
    int* result5 = filterList(test5, 5, &size5);
    printArray(result5, size5);
    free(result5);
    
    return 0;
}
