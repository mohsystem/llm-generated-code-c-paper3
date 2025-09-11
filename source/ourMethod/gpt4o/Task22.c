#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* integers;
    size_t size;
} IntArray;

IntArray filterList(const void** list, size_t size) {
    IntArray result;
    result.integers = malloc(size * sizeof(int));
    result.size = 0;
    
    for (size_t i = 0; i < size; ++i) {
        if (((intptr_t)list[i] & 1) == 0) {  // assume odd addresses for strings
            result.integers[result.size++] = (int)(intptr_t)list[i];
        }
    }
    return result;
}

void printIntArray(const IntArray* array) {
    for (size_t i = 0; i < array->size; ++i) {
        printf("%d ", array->integers[i]);
    }
    printf("\n");
}

int main() {
    const void* list1[] = {(void*)(intptr_t)1, (void*)(intptr_t)2, "a", "b"};
    const void* list2[] = {(void*)(intptr_t)1, "a", "b", (void*)(intptr_t)0, (void*)(intptr_t)15};
    const void* list3[] = {(void*)(intptr_t)1, (void*)(intptr_t)2, "a", "b", "aasf", "1", "123", (void*)(intptr_t)123};
    const void* list4[] = {"hello", "world", (void*)(intptr_t)3, (void*)(intptr_t)4};
    const void* list5[] = {(void*)(intptr_t)100, (void*)(intptr_t)200, "300"};

    IntArray result1 = filterList(list1, 4);
    IntArray result2 = filterList(list2, 5);
    IntArray result3 = filterList(list3, 8);
    IntArray result4 = filterList(list4, 4);
    IntArray result5 = filterList(list5, 3);

    printIntArray(&result1);
    printIntArray(&result2);
    printIntArray(&result3);
    printIntArray(&result4);
    printIntArray(&result5);

    free(result1.integers);
    free(result2.integers);
    free(result3.integers);
    free(result4.integers);
    free(result5.integers);

    return 0;
}