#include <stdio.h>
#include <stdlib.h>

long long find_outlier(const long long* arr, size_t len, int* err) {
    if (err == NULL) {
        return 0; /* Cannot report error status */
    }
    *err = 0;
    if (arr == NULL || len < 3) {
        *err = 1;
        return 0;
    }

    int evenCount = 0;
    for (size_t i = 0; i < 3; ++i) {
        if ((arr[i] % 2) == 0) {
            ++evenCount;
        }
    }
    int majorityEven = (evenCount >= 2) ? 1 : 0;

    long long outlier = 0;
    int mismatchCount = 0;
    for (size_t i = 0; i < len; ++i) {
        int isEven = ((arr[i] % 2) == 0) ? 1 : 0;
        if ((isEven && !majorityEven) || (!isEven && majorityEven)) {
            ++mismatchCount;
            outlier = arr[i];
            if (mismatchCount > 1) {
                break;
            }
        }
    }

    if (mismatchCount != 1) {
        *err = 2;
        return 0;
    }

    return outlier;
}

static void run_test(const long long* arr, size_t len, long long expected) {
    int err = 0;
    long long result = find_outlier(arr, len, &err);
    printf("Input: [");
    for (size_t i = 0; i < len; ++i) {
        printf("%lld", arr[i]);
        if (i + 1 < len) {
            printf(", ");
        }
    }
    if (err == 0) {
        printf("] -> Outlier: %lld | Expected: %lld\n", result, expected);
    } else {
        printf("] -> Error: %d\n", err);
    }
}

int main(void) {
    long long a1[] = {2, 4, 0, 100, 4, 11, 2602, 36};
    long long a2[] = {160, 3, 1719, 19, 11, 13, -21};
    long long a3[] = {1, 1, 2};
    long long a4[] = {2, -6, 8, -10, -3};
    long long a5[] = {3, 5, 7, 9, 2};

    run_test(a1, sizeof(a1)/sizeof(a1[0]), 11);
    run_test(a2, sizeof(a2)/sizeof(a2[0]), 160);
    run_test(a3, sizeof(a3)/sizeof(a3[0]), 2);
    run_test(a4, sizeof(a4)/sizeof(a4[0]), -3);
    run_test(a5, sizeof(a5)/sizeof(a5[0]), 2);

    return 0;
}