#include <stdio.h>
#include <stdlib.h>

// Structure to represent a tuple of two integers
typedef struct {
    int index1;
    int index2;
} Tuple;

// Function to find two numbers that add up to the target
Tuple two_sum(int nums[], int size, int target) {
    // Create a hash table to store numbers and their indices
     int *seen = (int *)malloc(20001 * sizeof(int)); // Assuming numbers are within -10000 to 10000 range
      for(int i =0; i<20001; i++){
          seen[i] = -1;
      }
    for (int i = 0; i < size; i++) {
         int complement = target - nums[i];
        int complementIndex = complement + 10000; // Adjust index for negative numbers
         if (complementIndex >=0 && complementIndex < 20001 && seen[complementIndex] != -1) {
             Tuple result = {seen[complementIndex], i};
             free(seen);
            return result;
        }
        seen[nums[i] + 10000] = i; // Adjust index for negative numbers
    }
     free(seen);

    Tuple result = {-1, -1}; // Should not happen since a solution is guaranteed
    return result;
}

int main() {
    int nums1[] = {1, 2, 3};
    Tuple result1 = two_sum(nums1, 3, 4);
    printf("{%d, %d}\n", result1.index1, result1.index2); // Output: {0, 2}

    int nums2[] = {3, 2, 4};
    Tuple result2 = two_sum(nums2, 3, 6);
    printf("{%d, %d}\n", result2.index1, result2.index2); // Output: {1, 2}


    int nums3[] = {10, 20, 30, 40};
    Tuple result3 = two_sum(nums3, 4, 50);
    printf("{%d, %d}\n", result3.index1, result3.index2); // Output: {0, 3}

    int nums4[] = {5, 7, 2, 9};
    Tuple result4 = two_sum(nums4, 4, 11);
    printf("{%d, %d}\n", result4.index1, result4.index2); // Output: {0, 2}

    int nums5[] = {-1, 5, 10, -7};
    Tuple result5 = two_sum(nums5, 4, 3);
    printf("{%d, %d}\n", result5.index1, result5.index2); // Output: {0, 2}
    return 0;
}