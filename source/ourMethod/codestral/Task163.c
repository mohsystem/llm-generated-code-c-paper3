#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int size;
    int elements[MAX_SIZE];
} Set;

void initSet(Set* set) {
    set->size = 0;
}

void addToSet(Set* set, int num) {
    set->elements[set->size++] = num;
}

int contains(Set* set, int num) {
    for (int i = 0; i < set->size; i++) {
        if (set->elements[i] == num) {
            return 1;
        }
    }
    return 0;
}

int longestRun(int* nums, int size) {
    if (size == 0) return 0;
    Set numSet;
    initSet(&numSet);
    for (int i = 0; i < size; i++) {
        addToSet(&numSet, nums[i]);
    }
    int maxLen = 1;
    for (int i = 0; i < numSet.size; i++) {
        int num = numSet.elements[i];
        if (!contains(&numSet, num - 1)) {
            int currNum = num;
            int currLen = 1;
            while (contains(&numSet, currNum + 1)) {
                currNum++;
                currLen++;
            }
            if (currLen > maxLen) {
                maxLen = currLen;
            }
        }
    }
    return maxLen;
}

int main() {
    int arr1[] = {1, 2, 3, 5, 6, 7, 8, 9};
    printf("%d\n", longestRun(arr1, sizeof(arr1) / sizeof(arr1[0]))); // 5
    int arr2[] = {1, 2, 3, 10, 11, 15};
    printf("%d\n", longestRun(arr2, sizeof(arr2) / sizeof(arr2[0]))); // 3
    int arr3[] = {5, 4, 2, 1};
    printf("%d\n", longestRun(arr3, sizeof(arr3) / sizeof(arr3[0]))); // 2
    int arr4[] = {3, 5, 7, 10, 15};
    printf("%d\n", longestRun(arr4, sizeof(arr4) / sizeof(arr4[0]))); // 1
    return 0;
}