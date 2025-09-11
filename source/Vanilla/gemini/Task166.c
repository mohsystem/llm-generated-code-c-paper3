#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort (ascending order)
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}


int *posNegSort(int arr[], int size) {
    int *pos = (int *)malloc(size * sizeof(int));
    int pos_count = 0;
    int *neg_indices = (int *)malloc(size * sizeof(int));
    int neg_count = 0;
    int *neg_values = (int *)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
            pos[pos_count++] = arr[i];
        } else {
            neg_indices[neg_count] = i;
            neg_values[neg_count++] = arr[i];
        }
    }

    qsort(pos, pos_count, sizeof(int), compare);

    int *result = (int *)malloc(size * sizeof(int));
    int pos_index = 0;
    int neg_index = 0;
    for (int i = 0; i < size; i++) {
        if (pos_index < pos_count && (neg_count == 0 || i < neg_indices[neg_index])) {
            result[i] = pos[pos_index++];
        } else if (neg_count > 0 && i == neg_indices[neg_index]) {
            result[i] = neg_values[neg_index++];
        }
    }

    free(pos);
    free(neg_indices);
    free(neg_values);
    return result;
}

int main() {
    int test1[] = {6, 3, -2, 5, -8, 2, -2};
    int size1 = sizeof(test1) / sizeof(test1[0]);
    int *result1 = posNegSort(test1, size1);
    for (int i = 0; i < size1; i++) printf("%d ", result1[i]);
    printf("\n");
    free(result1);

    int test2[] = {6, 5, 4, -1, 3, 2, -1, 1};
    int size2 = sizeof(test2) / sizeof(test2[0]);
    int *result2 = posNegSort(test2, size2);
    for (int i = 0; i < size2; i++) printf("%d ", result2[i]);
    printf("\n");
    free(result2);


    int test3[] = {-5, -5, -5, -5, 7, -5};
    int size3 = sizeof(test3) / sizeof(test3[0]);
    int *result3 = posNegSort(test3, size3);
    for (int i = 0; i < size3; i++) printf("%d ", result3[i]);
    printf("\n");
    free(result3);


    int test4[] = {};
    int size4 = sizeof(test4) / sizeof(test4[0]);
    int *result4 = posNegSort(test4, size4);
    for (int i = 0; i < size4; i++) printf("%d ", result4[i]);
    printf("\n");
    free(result4);

    int test5[] = {1, 2, 3, 4, -1, -2, -3};
    int size5 = sizeof(test5) / sizeof(test5[0]);
    int *result5 = posNegSort(test5, size5);
    for (int i = 0; i < size5; i++) printf("%d ", result5[i]);
    printf("\n");
    free(result5);


    return 0;
}