#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int* temp;
    long count;
} Task171;

Task171* createTask171() {
    Task171* task = malloc(sizeof(Task171));
    task->count = 0;
    return task;
}

void destroyTask171(Task171* task) {
    free(task->temp);
    free(task);
}

void sort(Task171* task, int* nums, int start, int end) {
    if (start >= end) {
        return;
    }
    int mid = start + (end - start) / 2;
    sort(task, nums, start, mid);
    sort(task, nums, mid + 1, end);
    merge(task, nums, start, mid, end);
}

void merge(Task171* task, int* nums, int start, int mid, int end) {
    for (int i = start, j = mid + 1; i <= mid; i++) {
        while (j <= end && nums[i] / 2.0 > nums[j]) {
            j++;
        }
        task->count += j - (mid + 1);
    }

    int i = start, j = mid + 1, k = 0;
    while (i <= mid && j <= end) {
        task->temp[k++] = nums[i] <= nums[j] ? nums[i++] : nums[j++];
    }
    while (i <= mid) {
        task->temp[k++] = nums[i++];
    }
    while (j <= end) {
        task->temp[k++] = nums[j++];
    }
    for (i = start, k = 0; i <= end; i++, k++) {
        nums[i] = task->temp[k];
    }
}

int reversePairs(Task171* task, int* nums, int numsSize) {
    task->temp = malloc(sizeof(int) * numsSize);
    sort(task, nums, 0, numsSize - 1);
    int result = task->count;
    free(task->temp);
    return result;
}

int main() {
    Task171* task = createTask171();
    int nums1[] = {1,3,2,3,1};
    int nums2[] = {2,4,3,5,1};
    int nums3[] = {2147483647,2147483647,-2147483647,-2147483647,2147483647,2147483647,-2147483647,-2147483647};
    int nums4[] = {-2147483647,-2147483648,2147483647,2147483647,2147483647,2147483646,2147483646,2147483646,-2147483646};
    int nums5[] = {5,4,3,2,1};
    printf("%d\n", reversePairs(task, nums1, sizeof(nums1)/sizeof(nums1[0])));
    printf("%d\n", reversePairs(task, nums2, sizeof(nums2)/sizeof(nums2[0])));
    printf("%d\n", reversePairs(task, nums3, sizeof(nums3)/sizeof(nums3[0])));
    printf("%d\n", reversePairs(task, nums4, sizeof(nums4)/sizeof(nums4[0])));
    printf("%d\n", reversePairs(task, nums5, sizeof(nums5)/sizeof(nums5[0])));
    destroyTask171(task);
    return 0;
}