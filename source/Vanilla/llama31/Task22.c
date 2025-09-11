#include <stdio.h>
#include <stdlib.h>

// Since C does not support mixed types in arrays directly, we will use a struct to simulate this
typedef struct {
    int is_int;
    union {
        int int_val;
        char* str_val;
    } value;
} MixedType;

MixedType* filterList(MixedType* input_list, int size, int* new_size) {
    MixedType* result = (MixedType*)malloc(size * sizeof(MixedType));
    *new_size = 0;

    for (int i = 0; i < size; i++) {
        if (input_list[i].is_int) {
            result[*new_size].is_int = 1;
            result[*new_size].value.int_val = input_list[i].value.int_val;
            (*new_size)++;
        }
    }

    return result;
}

int main() {
    // Test cases
    MixedType test1[] = {{1, {1}}, {1, {2}}, {0, {"a"}}, {0, {"b"}}};
    MixedType test2[] = {{1, {1}}, {0, {"a"}}, {0, {"b"}}, {1, {0}}, {1, {15}}};
    MixedType test3[] = {{1, {1}}, {1, {2}}, {0, {"a"}}, {0, {"b"}}, {0, {"aasf"}}, {0, {"1"}}, {0, {"123"}}, {1, {123}}};

    int size1 = sizeof(test1) / sizeof(test1[0]);
    int size2 = sizeof(test2) / sizeof(test2[0]);
    int size3 = sizeof(test3) / sizeof(test3[0]);

    int new_size1, new_size2, new_size3;
    MixedType* result1 = filterList(test1, size1, &new_size1);
    MixedType* result2 = filterList(test2, size2, &new_size2);
    MixedType* result3 = filterList(test3, size3, &new_size3);

    for (int i = 0; i < new_size1; i++) {
        printf("%d ", result1[i].value.int_val);
    }
    printf("\n");

    for (int i = 0; i < new_size2; i++) {
        printf("%d ", result2[i].value.int_val);
    }
    printf("\n");

    for (int i = 0; i < new_size3; i++) {
        printf("%d ", result3[i].value.int_val);
    }
    printf("\n");

    free(result1);
    free(result2);
    free(result3);

    return 0;
}