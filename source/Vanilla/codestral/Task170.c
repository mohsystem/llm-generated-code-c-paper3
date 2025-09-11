#include <stdio.h>
#include <stdlib.h>

int cmpfunc (const void * a, const void * b) {
   return ( *(long*)a - *(long*)b );
}

int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    long* sums = (long*)malloc((numsSize + 1) * sizeof(long));
    sums[0] = 0;
    for (int i = 0; i < numsSize; ++i)
        sums[i + 1] = sums[i] + nums[i];

    int count = 0;
    long* cache = (long*)malloc(numsSize * sizeof(long));
    for (int i = 0; i < numsSize; ++i) {
        for (int j = i; j <= numsSize; ++j) {
            long sum = sums[j] - sums[i];
            if (sum >= lower && sum <= upper)
                count++;
        }
        cache[i] = sums[i];
    }

    qsort(cache, numsSize, sizeof(long), cmpfunc);
    for (int i = 0; i <= numsSize; ++i)
        sums[i] = cache[i];

    free(cache);
    free(sums);
    return count;
}

int main() {
    printf("%d\n", countRangeSum((int[]){-2,5,-1}, 3, -2, 2)); // 3
    printf("%d\n", countRangeSum((int[]){0}, 1, 0, 0)); // 1
    // Add more test cases here
    return 0;
}