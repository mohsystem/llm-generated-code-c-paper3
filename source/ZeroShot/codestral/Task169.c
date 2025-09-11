#include <stdio.h>
#include <stdlib.h>

int* bit;
int n;

void update(int x) {
    for (; x <= n; x += x & -x) {
        bit[x]++;
    }
}

int query(int x) {
    int ans = 0;
    for (; x > 0; x -= x & -x) {
        ans += bit[x];
    }
    return ans;
}

int cmp(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int* countSmaller(int* nums, int numsSize, int* returnSize) {
    int* sorted_nums = (int*)malloc(numsSize * sizeof(int));
    memcpy(sorted_nums, nums, numsSize * sizeof(int));
    qsort(sorted_nums, numsSize, sizeof(int), cmp);

    int* ranks = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        ranks[i] = (int)(bsearch(&nums[i], sorted_nums, numsSize, sizeof(int), cmp) - sorted_nums);
    }

    n = numsSize;
    bit = (int*)calloc((n + 1), sizeof(int));
    int* res = (int*)malloc(numsSize * sizeof(int));
    for (int i = numsSize - 1; i >= 0; i--) {
        res[i] = query(ranks[i]);
        update(ranks[i] + 1);
    }

    *returnSize = numsSize;
    free(sorted_nums);
    free(ranks);
    free(bit);
    return res;
}

int main() {
    int nums[] = {5,2,6,1};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize;
    int* res = countSmaller(nums, numsSize, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", res[i]);
    }
    free(res);
    return 0;
}