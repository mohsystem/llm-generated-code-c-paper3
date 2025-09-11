#include <stdio.h>
#include <stdlib.h>

// Structure to represent a tuple of two integers
struct Tuple {
    int index1;
    int index2;
};

// Function to find two numbers that add up to the target
struct Tuple two_sum(int numbers[], int size, int target) {
    // Create a hash table to store numbers and their indices
    int *numMap = (int *)malloc(10000 * sizeof(int)); // Adjust size as needed
     for(int i = 0; i < 10000; i++) {
        numMap[i] = -1;
     }


    for (int i = 0; i < size; i++) {
        int complement = target - numbers[i];
        
        if (numMap[complement + 5000] != -1) {
           struct Tuple result = {numMap[complement + 5000], i};
           free(numMap);
           return result;

        }
        numMap[numbers[i] + 5000] = i; // Add 5000 to handle negative numbers
    }
     struct Tuple result = {-1,-1};
    free(numMap);
    return result; // Should not reach here as per problem statement
}

int main() {
    int test1[] = {1, 2, 3};
    int target1 = 4;
    struct Tuple result1 = two_sum(test1, 3, target1);
    printf("%d %d\n", result1.index1, result1.index2); // Output: 0 2

    int test2[] = {3, 2, 4};
    int target2 = 6;
    struct Tuple result2 = two_sum(test2, 3, target2);
    printf("%d %d\n", result2.index1, result2.index2); // Output: 1 2

    int test3[] = {10, 20, 30, 40};
    int target3 = 50;
    struct Tuple result3 = two_sum(test3, 4, target3);
    printf("%d %d\n", result3.index1, result3.index2); // Output: 1 2

    int test4[] = {1, -2, 3, 4};
    int target4 = 2;
    struct Tuple result4 = two_sum(test4, 4, target4);
    printf("%d %d\n", result4.index1, result4.index2); // Output: 1 2

    int test5[] = {2, 2, 3};
    int target5 = 4;
    struct Tuple result5 = two_sum(test5, 3, target5);
    printf("%d %d\n", result5.index1, result5.index2); // Output: 0 1


    return 0;
}