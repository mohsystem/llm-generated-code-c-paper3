#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int is_int;
    union {
        int int_val;
        char* str_val;
    } data;
} Item;

int* filterList(Item* list, int size, int* returnSize) {
    int* result = malloc(size * sizeof(int));
    *returnSize = 0;
    for (int i = 0; i < size; ++i) {
        if (list[i].is_int) {
            result[(*returnSize)++] = list[i].data.int_val;
        }
    }
    return result;
}

int main() {
    Item list1[] = {{1, {1}}, {1, {2}}, {0, {.str_val = "a"}}, {0, {.str_val = "b"}}};
    Item list2[] = {{1, {1}}, {0, {.str_val = "a"}}, {0, {.str_val = "b"}}, {1, {0}}, {1, {15}}};
    Item list3[] = {{1, {1}}, {1, {2}}, {0, {.str_val = "a"}}, {0, {.str_val = "b"}}, {0, {.str_val = "aasf"}}, {0, {.str_val = "1"}}, {0, {.str_val = "123"}}, {1, {123}}};
    Item list4[] = {{0, {.str_val = "hello"}}, {1, {3}}, {0, {.str_val = "world"}}, {1, {4}}};
    Item list5[] = {{1, {5}}, {1, {6}}, {0, {.str_val = "test"}}, {1, {7}}, {0, {.str_val = "filter"}}};

    int returnSize;

    int* result1 = filterList(list1, 4, &returnSize);
    for (int i = 0; i < returnSize; ++i) printf("%d ", result1[i]);
    printf("\n");
    free(result1);

    int* result2 = filterList(list2, 5, &returnSize);
    for (int i = 0; i < returnSize; ++i) printf("%d ", result2[i]);
    printf("\n");
    free(result2);

    int* result3 = filterList(list3, 8, &returnSize);
    for (int i = 0; i < returnSize; ++i) printf("%d ", result3[i]);
    printf("\n");
    free(result3);

    int* result4 = filterList(list4, 4, &returnSize);
    for (int i = 0; i < returnSize; ++i) printf("%d ", result4[i]);
    printf("\n");
    free(result4);

    int* result5 = filterList(list5, 5, &returnSize);
    for (int i = 0; i < returnSize; ++i) printf("%d ", result5[i]);
    printf("\n");
    free(result5);

    return 0;
}