#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
#include <stdint.h>

typedef struct {
    int* data;
    size_t len;
} IntArray;

static IntArray remove_smallest(const int* arr, size_t len) {
    IntArray res;
    res.data = NULL;
    res.len = 0;

    if (arr == NULL || len == 0) {
        return res;
    }

    size_t min_idx = 0;
    int min_val = arr[0];
    for (size_t i = 1; i < len; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
            min_idx = i;
        }
    }

    if (len - 1 == 0) {
        return res; /* empty result */
    }

    if ((len - 1) > SIZE_MAX / sizeof(int)) {
        return res; /* fail closed */
    }

    res.len = len - 1;
    res.data = (int*)calloc(res.len, sizeof(int));
    if (res.data == NULL) {
        res.len = 0;
        return res;
    }

    size_t k = 0;
    for (size_t i = 0; i < len; i++) {
        if (i != min_idx) {
            res.data[k++] = arr[i];
        }
    }

    return res;
}

static void print_array(const int* arr, size_t len) {
    printf("[");
    for (size_t i = 0; i < len; i++) {
        if (i > 0) printf(",");
        printf("%d", arr[i]);
    }
    printf("]");
}

int main(void) {
    int a1[] = {1,2,3,4,5};
    int a2[] = {5,3,2,1,4};
    int a3[] = {2,2,1,2,1};
    /* Empty input represented by NULL and length 0 */
    int* a4 = NULL;
    size_t len4 = 0;
    int a5[] = {-3,-1,-3,0};

    struct {
        const int* data;
        size_t len;
    } tests[5] = {
        {a1, sizeof(a1)/sizeof(a1[0])},
        {a2, sizeof(a2)/sizeof(a2[0])},
        {a3, sizeof(a3)/sizeof(a3[0])},
        {a4, len4},
        {a5, sizeof(a5)/sizeof(a5[0])}
    };

    for (size_t i = 0; i < 5; i++) {
        const int* input = tests[i].data;
        size_t in_len = tests[i].len;
        IntArray out = remove_smallest(input, in_len);

        printf("Input:  ");
        print_array(input, in_len);
        printf("\n");

        printf("Output: ");
        print_array(out.data, out.len);
        printf("\n---\n");

        free(out.data);
    }

    return 0;
}