#include <stdio.h>
#include <stdlib.h>

// Structure to represent a tuple of two integers
typedef struct {
    int index1;
    int index2;
} Tuple;


Tuple* two_sum(int nums[], int numsSize, int target) {
    // Allocate memory for the hash table (can be optimized)
     Tuple *result = (Tuple*)malloc(sizeof(Tuple));
     if (result == NULL) {
        return NULL; // Handle memory allocation failure
     }
    for(int i =0; i < numsSize ; i++){
        for (int j = i+1; j < numsSize; j++){
            if (nums[i] + nums[j] == target){
                result->index1 = i;
                result->index2 = j;
                return result;
            }
        }
    }
    return NULL;
}

int main() {
    int nums1[] = {1, 2, 3};
    int target1 = 4;
    Tuple* result1 = two_sum(nums1, 3, target1);
    if (result1 != NULL) {
        printf("[%d, %d]\n", result1->index1, result1->index2);
        free(result1);
    }

    int nums2[] = {3, 2, 4};
    int target2 = 6;
    Tuple* result2 = two_sum(nums2, 3, target2);
    if (result2 != NULL) {
        printf("[%d, %d]\n", result2->index1, result2->index2);
        free(result2);
    }

    int nums3[] = {2, 7, 11, 15};
    int target3 = 9;
    Tuple* result3 = two_sum(nums3, 4, target3);
    if (result3 != NULL) {
        printf("[%d, %d]\n", result3->index1, result3->index2);
        free(result3);
    }

    int nums4[] = {3, 3};
    int target4 = 6;
    Tuple* result4 = two_sum(nums4, 2, target4);
    if (result4 != NULL) {
        printf("[%d, %d]\n", result4->index1, result4->index2);
        free(result4);
    }

    int nums5[] = {3, 2, 3};
    int target5 = 6;
    Tuple* result5 = two_sum(nums5, 3, target5);
    if (result5 != NULL) {
        printf("[%d, %d]\n", result5->index1, result5->index2);
        free(result5);
    }

    return 0;
}