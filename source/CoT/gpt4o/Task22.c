#include <stdio.h>

void filterList(const void* list[], size_t size, int result[], size_t* resultSize) {
    *resultSize = 0;
    for (size_t i = 0; i < size; i++) {
        if (((int*)list[i]) != NULL) {
            result[*resultSize] = *(int*)list[i];
            (*resultSize)++;
        }
    }
}

int main() {
    const void* list1[] = {(int[]){1}, (int[]){2}, "a", "b"};
    const void* list2[] = {(int[]){1}, "a", "b", (int[]){0}, (int[]){15}};
    const void* list3[] = {(int[]){1}, (int[]){2}, "a", "b", "aasf", "1", "123", (int[]){123}};
    const void* list4[] = {"x", "y", "z"};
    const void* list5[] = {(int[]){10}, (int[]){20}, (int[]){30}, "40", "fifty"};

    int result[10];
    size_t resultSize;

    filterList(list1, 4, result, &resultSize);
    for (size_t i = 0; i < resultSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    filterList(list2, 5, result, &resultSize);
    for (size_t i = 0; i < resultSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    filterList(list3, 8, result, &resultSize);
    for (size_t i = 0; i < resultSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    filterList(list4, 3, result, &resultSize);
    for (size_t i = 0; i < resultSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    filterList(list5, 5, result, &resultSize);
    for (size_t i = 0; i < resultSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}