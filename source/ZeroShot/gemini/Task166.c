#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int *posNegSort(int nums[], int size, int *result_size) {
    int *pos = (int *)malloc(size * sizeof(int));
    int pos_count = 0;
    int *result = (int *)malloc(size * sizeof(int));
    *result_size = 0;

    for (int i = 0; i < size; i++) {
        if (nums[i] > 0) {
            pos[pos_count++] = nums[i];
        }
    }

    qsort(pos, pos_count, sizeof(int), compare);

    int pos_index = 0;
    for (int i = 0; i < size; i++) {
        if (nums[i] > 0) {
            result[(*result_size)++] = pos[pos_index++];
        } else {
            result[(*result_size)++] = nums[i];
        }
    }

    free(pos);
    return result;
}

int main() {
    int test1[] = {6, 3, -2, 5, -8, 2, -2};
    int size1 = sizeof(test1) / sizeof(test1[0]);
    int result_size1;
    int *result1 = posNegSort(test1, size1, &result_size1);
    for (int i = 0; i < result_size1; i++) {
        printf("%d ", result1[i]);
    }
    printf("\n");
    free(result1);

    // Test cases 2-5 are similar to the above.
    // ...


    return 0;
}