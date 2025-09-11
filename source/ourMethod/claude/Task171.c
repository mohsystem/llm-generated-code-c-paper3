
#include <stdio.h>
#include <stdlib.h>

int merge(int* nums, int low, int mid, int high) {
    int count = 0;
    int j = mid + 1;
    for (int i = low; i <= mid; i++) {
        while (j <= high && nums[i] > 2LL * nums[j]) {
            j++;
        }
        count += j - (mid + 1);
    }
    
    int* temp = (int*)malloc((high - low + 1) * sizeof(int));
    int left = low, right = mid + 1, k = 0;
    
    while (left <= mid && right <= high) {
        if (nums[left] <= nums[right]) {
            temp[k++] = nums[left++];
        } else {
            temp[k++] = nums[right++];
        }
    }
    
    while (left <= mid) {
        temp[k++] = nums[left++];
    }
    while (right <= high) {
        temp[k++] = nums[right++];
    }
    
    for (int i = 0; i < k; i++) {
        nums[low + i] = temp[i];
    }
    
    free(temp);
    return count;
}

int mergeSort(int* nums, int low, int high) {
    if (low >= high) return 0;
    
    int mid = low + (high - low) / 2;
    int count = mergeSort(nums, low, mid);
    count += mergeSort(nums, mid + 1, high);
    count += merge(nums, low, mid, high);
    
    return count;
}

int reversePairs(int* nums, int numsSize) {
    if (nums == NULL || numsSize < 2) return 0;
    return mergeSort(nums, 0, numsSize - 1);
}

int main() {
    // Test cases
    int test1[] = {1, 3, 2, 3, 1};
    int test2[] = {2, 4, 3, 5, 1};
    int test3[] = {1, 1, 1, 1, 1};
    int test4[] = {5, 4, 3, 2, 1};
    int test5[] = {1};
    
    printf("Test case 1: %d\\n", reversePairs(test1, 5));
    printf("Test case 2: %d\\n", reversePairs(test2, 5));
    printf("Test case 3: %d\\n", reversePairs(test3, 5));
    printf("Test case 4: %d\\n", reversePairs(test4, 5));
    printf("Test case 5: %d\\n", reversePairs(test5, 1));
    
    return 0;
}
