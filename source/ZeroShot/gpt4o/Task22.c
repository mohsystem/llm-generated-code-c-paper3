#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
} IntList;

IntList filterList(void **list, size_t size) {
    IntList result;
    result.data = (int *)malloc(size * sizeof(int));
    result.size = 0;
    for (size_t i = 0; i < size; ++i) {
        if (*(int *)list[i] == 1) { // using a flag to differentiate int and string
            result.data[result.size++] = (int)(intptr_t)list[i];
        }
    }
    return result;
}

int main() {
    void *test1[] = {(void *)(intptr_t)1, (void *)(intptr_t)2, "a", "b"};
    void *test2[] = {(void *)(intptr_t)1, "a", "b", (void *)(intptr_t)0, (void *)(intptr_t)15};
    void *test3[] = {(void *)(intptr_t)1, (void *)(intptr_t)2, "a", "b", "aasf", "1", "123", (void *)(intptr_t)123};
    void *test4[] = {"test", "filter", (void *)(intptr_t)123, (void *)(intptr_t)456};
    void *test5[] = {(void *)(intptr_t)10, (void *)(intptr_t)20, "30", (void *)(intptr_t)40, "50"};

    IntList result1 = filterList(test1, 4);
    for (size_t i = 0; i < result1.size; ++i) printf("%d ", result1.data[i]);
    printf("\n");

    IntList result2 = filterList(test2, 5);
    for (size_t i = 0; i < result2.size; ++i) printf("%d ", result2.data[i]);
    printf("\n");

    IntList result3 = filterList(test3, 8);
    for (size_t i = 0; i < result3.size; ++i) printf("%d ", result3.data[i]);
    printf("\n");

    IntList result4 = filterList(test4, 4);
    for (size_t i = 0; i < result4.size; ++i) printf("%d ", result4.data[i]);
    printf("\n");

    IntList result5 = filterList(test5, 5);
    for (size_t i = 0; i < result5.size; ++i) printf("%d ", result5.data[i]);
    printf("\n");

    free(result1.data);
    free(result2.data);
    free(result3.data);
    free(result4.data);
    free(result5.data);

    return 0;
}