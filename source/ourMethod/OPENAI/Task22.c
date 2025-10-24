#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT = 0,
    TYPE_STR = 1
} TypeTag;

typedef struct {
    TypeTag type;
    int i;
    const char* s;
} Value;

typedef struct {
    int* data;
    size_t size;
    int ok; /* 1 on success, 0 on error */
} IntArray;

static void free_int_array(IntArray* arr) {
    if (arr != NULL && arr->data != NULL) {
        free(arr->data);
        arr->data = NULL;
        arr->size = 0;
        arr->ok = 0;
    }
}

IntArray filter_list(const Value* arr, size_t n) {
    IntArray result;
    result.data = NULL;
    result.size = 0;
    result.ok = 0;

    if (arr == NULL && n != 0) {
        return result;
    }

    int* temp = (int*)malloc(n > 0 ? n * sizeof(int) : sizeof(int));
    if (temp == NULL) {
        return result;
    }

    size_t count = 0;
    for (size_t i = 0; i < n; ++i) {
        if (arr[i].type == TYPE_INT) {
            if (arr[i].i < 0) {
                free(temp);
                return result; /* fail closed on negative int */
            }
            temp[count++] = arr[i].i;
        } else if (arr[i].type == TYPE_STR) {
            /* skip strings */
            continue;
        } else {
            free(temp);
            return result; /* fail closed on unknown type */
        }
    }

    int* out = NULL;
    if (count > 0) {
        out = (int*)malloc(count * sizeof(int));
        if (out == NULL) {
            free(temp);
            return result;
        }
        for (size_t i = 0; i < count; ++i) {
            out[i] = temp[i];
        }
    }
    free(temp);

    result.data = out;
    result.size = count;
    result.ok = 1;
    return result;
}

static void print_int_array(const IntArray* arr) {
    if (arr == NULL || !arr->ok) {
        printf("[]\n");
        return;
    }
    printf("[");
    for (size_t i = 0; i < arr->size; ++i) {
        if (i > 0) printf(", ");
        printf("%d", arr->data[i]);
    }
    printf("]\n");
}

int main(void) {
    Value t1[] = { {TYPE_INT, 1, NULL}, {TYPE_INT, 2, NULL}, {TYPE_STR, 0, "a"}, {TYPE_STR, 0, "b"} };
    Value t2[] = { {TYPE_INT, 1, NULL}, {TYPE_STR, 0, "a"}, {TYPE_STR, 0, "b"}, {TYPE_INT, 0, NULL}, {TYPE_INT, 15, NULL} };
    Value t3[] = { {TYPE_INT, 1, NULL}, {TYPE_INT, 2, NULL}, {TYPE_STR, 0, "a"}, {TYPE_STR, 0, "b"}, {TYPE_STR, 0, "aasf"}, {TYPE_STR, 0, "1"}, {TYPE_STR, 0, "123"}, {TYPE_INT, 123, NULL} };
    Value t4[] = { {TYPE_STR, 0, "hello"}, {TYPE_STR, 0, "world"} };
    Value t5[] = { {TYPE_INT, 0, NULL}, {TYPE_INT, 99, NULL}, {TYPE_STR, 0, "x"}, {TYPE_STR, 0, "y"}, {TYPE_INT, 42, NULL} };

    IntArray r1 = filter_list(t1, sizeof(t1)/sizeof(t1[0]));
    IntArray r2 = filter_list(t2, sizeof(t2)/sizeof(t2[0]));
    IntArray r3 = filter_list(t3, sizeof(t3)/sizeof(t3[0]));
    IntArray r4 = filter_list(t4, sizeof(t4)/sizeof(t4[0]));
    IntArray r5 = filter_list(t5, sizeof(t5)/sizeof(t5[0]));

    print_int_array(&r1); /* [1, 2] */
    print_int_array(&r2); /* [1, 0, 15] */
    print_int_array(&r3); /* [1, 2, 123] */
    print_int_array(&r4); /* [] */
    print_int_array(&r5); /* [0, 99, 42] */

    free_int_array(&r1);
    free_int_array(&r2);
    free_int_array(&r3);
    free_int_array(&r4);
    free_int_array(&r5);

    return 0;
}