#include <stdio.h>
#include <stddef.h>

int find_even_index(const long long *arr, size_t n) {
    if (arr == NULL) return -1;
    if (n < 1 || n >= 1000) return -1;

    long long total = 0;
    for (size_t i = 0; i < n; i++) {
        total += arr[i];
    }

    long long left = 0;
    for (size_t i = 0; i < n; i++) {
        long long right = total - left - arr[i];
        if (left == right) {
            if (i > (size_t)0x7FFFFFFF) return -1; /* ensure int range */
            return (int)i;
        }
        left += arr[i];
    }
    return -1;
}

int main(void) {
    long long t1[] = {1, 2, 3, 4, 3, 2, 1};
    long long t2[] = {1, 100, 50, -51, 1, 1};
    long long t3[] = {20, 10, -80, 10, 10, 15, 35};
    long long t4[] = {1, 2, 3, 4, 5, 6};
    long long t5[] = {0, 0, 0, 0};

    printf("%d\n", find_even_index(t1, sizeof(t1) / sizeof(t1[0])));
    printf("%d\n", find_even_index(t2, sizeof(t2) / sizeof(t2[0])));
    printf("%d\n", find_even_index(t3, sizeof(t3) / sizeof(t3[0])));
    printf("%d\n", find_even_index(t4, sizeof(t4) / sizeof(t4[0])));
    printf("%d\n", find_even_index(t5, sizeof(t5) / sizeof(t5[0])));

    return 0;
}