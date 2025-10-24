#include <stdio.h>

/**
 * @brief Finds an index N in an array of integers where the sum of the integers
 * to the left of N is equal to the sum of the integers to the right of N.
 *
 * @param arr A pointer to a constant integer array.
 * @param size The number of elements in the array.
 * @return The lowest index N where the left side sum equals the right side sum.
 *         Returns -1 if no such index is found or input is invalid.
 */
int findEvenIndex(const int arr[], int size) {
    if (arr == NULL || size <= 0) {
        return -1;
    }

    long long totalSum = 0;
    for (int i = 0; i < size; i++) {
        totalSum += arr[i];
    }

    long long leftSum = 0;
    for (int i = 0; i < size; i++) {
        // The right sum is the total sum minus the left sum and the current element
        long long rightSum = totalSum - leftSum - arr[i];

        if (leftSum == rightSum) {
            return i;
        }
        
        leftSum += arr[i];
    }

    return -1;
}

void print_array(const int arr[], int size) {
    printf("{");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(",");
        }
    }
    printf("}");
}

int main() {
    // Test Case 1
    int test1[] = {1, 2, 3, 4, 3, 2, 1};
    int size1 = sizeof(test1) / sizeof(test1[0]);
    printf("Input: ");
    print_array(test1, size1);
    printf(", Output: %d\n", findEvenIndex(test1, size1));

    // Test Case 2
    int test2[] = {1, 100, 50, -51, 1, 1};
    int size2 = sizeof(test2) / sizeof(test2[0]);
    printf("Input: ");
    print_array(test2, size2);
    printf(", Output: %d\n", findEvenIndex(test2, size2));

    // Test Case 3
    int test3[] = {20, 10, -80, 10, 10, 15, 35};
    int size3 = sizeof(test3) / sizeof(test3[0]);
    printf("Input: ");
    print_array(test3, size3);
    printf(", Output: %d\n", findEvenIndex(test3, size3));

    // Test Case 4: index is at the end
    int test4[] = {10, -80, 10, 10, 15, 35, 20};
    int size4 = sizeof(test4) / sizeof(test4[0]);
    printf("Input: ");
    print_array(test4, size4);
    printf(", Output: %d\n", findEvenIndex(test4, size4));

    // Test Case 5: no solution
    int test5[] = {1, 2, 3, 4, 5, 6};
    int size5 = sizeof(test5) / sizeof(test5[0]);
    printf("Input: ");
    print_array(test5, size5);
    printf(", Output: %d\n", findEvenIndex(test5, size5));

    return 0;
}