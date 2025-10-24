#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int queueTime(const int* customers, size_t len, int n) {
    if (customers == NULL || n <= 0) {
        return -1; /* invalid input */
    }
    for (size_t i = 0; i < len; ++i) {
        if (customers[i] < 0) {
            return -1; /* invalid customer time */
        }
    }
    if (len == 0) {
        return 0;
    }
    int k = n < (int)len ? n : (int)len;
    int* tills = (int*)calloc((size_t)k, sizeof(int));
    if (tills == NULL) {
        return -1; /* allocation failure */
    }

    for (size_t i = 0; i < len; ++i) {
        int min_idx = 0;
        int min_val = tills[0];
        for (int j = 1; j < k; ++j) {
            if (tills[j] < min_val) {
                min_val = tills[j];
                min_idx = j;
            }
        }
        tills[min_idx] += customers[i];
    }

    int max_val = 0;
    for (int j = 0; j < k; ++j) {
        if (tills[j] > max_val) {
            max_val = tills[j];
        }
    }

    free(tills);
    return max_val;
}

int main(void) {
    int arr1[] = {5, 3, 4};
    int arr2[] = {10, 2, 3, 3};
    int arr3[] = {2, 3, 10};
    int arr4[] = {};
    int arr5[] = {1, 2, 3, 4, 5};

    printf("Test 1 result: %d\n", queueTime(arr1, sizeof(arr1)/sizeof(arr1[0]), 1));
    printf("Test 2 result: %d\n", queueTime(arr2, sizeof(arr2)/sizeof(arr2[0]), 2));
    printf("Test 3 result: %d\n", queueTime(arr3, sizeof(arr3)/sizeof(arr3[0]), 2));
    printf("Test 4 result: %d\n", queueTime(arr4, sizeof(arr4)/sizeof(arr4[0]), 1));
    printf("Test 5 result: %d\n", queueTime(arr5, sizeof(arr5)/sizeof(arr5[0]), 100));

    return 0;
}