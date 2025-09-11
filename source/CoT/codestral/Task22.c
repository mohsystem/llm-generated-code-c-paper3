#include <stdio.h>
#include <stdlib.h>

enum Type {
    INT,
    STR
};

struct Item {
    enum Type type;
    union {
        int i;
        char* s;
    } value;
};

void filterList(struct Item* list, int size, int** result, int* resultSize) {
    *resultSize = 0;
    *result = (int*)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        if (list[i].type == INT) {
            (*result)[(*resultSize)++] = list[i].value.i;
        }
    }
}

int main() {
    struct Item list1[] = {{INT, {1}}, {INT, {2}}, {STR, {"a"}}, {STR, {"b"}}};
    int* result1;
    int resultSize1;
    filterList(list1, 4, &result1, &resultSize1);
    for (int i = 0; i < resultSize1; i++) {
        printf("%d ", result1[i]);
    }
    printf("\n"); // Output: 1 2
    free(result1);

    struct Item list2[] = {{INT, {1}}, {STR, {"a"}}, {STR, {"b"}}, {INT, {0}}, {INT, {15}}};
    int* result2;
    int resultSize2;
    filterList(list2, 5, &result2, &resultSize2);
    for (int i = 0; i < resultSize2; i++) {
        printf("%d ", result2[i]);
    }
    printf("\n"); // Output: 1 0 15
    free(result2);

    struct Item list3[] = {{INT, {1}}, {INT, {2}}, {STR, {"a"}}, {STR, {"b"}}, {STR, {"aasf"}}, {STR, {"1"}}, {STR, {"123"}}, {INT, {123}}};
    int* result3;
    int resultSize3;
    filterList(list3, 8, &result3, &resultSize3);
    for (int i = 0; i < resultSize3; i++) {
        printf("%d ", result3[i]);
    }
    printf("\n"); // Output: 1 2 123
    free(result3);

    return 0;
}