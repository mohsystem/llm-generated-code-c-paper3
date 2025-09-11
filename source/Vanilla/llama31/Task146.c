#include <stdio.h>
#include <stdlib.h>

int missingNumber(int arr[], int n) {
    int* hash = (int*)calloc(n + 2, sizeof(int));
    for (int i = 0; i < n; i++) {
        hash[arr[i]]++;
    }
    for (int i = 1; i <= n + 1; i++) {
        if (hash[i] == 0) {
            free(hash);
            return i;
        }
    }
    free(hash);
    return -1;
}

int main() {
    int arr1[] = {1, 2, 4, 5};
    int arr2[] = {1, 2, 3, 5};
    int arr3[] = {1, 3, 4, 5};
    int arr4[] = {2, 3, 4, 5};
    int arr5[] = {1, 2, 3, 4};

    printf("The missing number is: %d\n", missingNumber(arr1, 4));
    printf("The missing number is: %d\n", missingNumber(arr2, 4));
    printf("The missing number is: %d\n", missingNumber(arr3, 4));
    printf("The missing number is: %d\n", missingNumber(arr4, 4));
    printf("The missing number is: %d\n", missingNumber(arr5, 4));

    return 0;
}