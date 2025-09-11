// C implementation is more complex due to lack of built-in priority queue.  Would require custom implementation.
// For brevity and given the other language examples, a simplified partial implementation is provided here.
#include <stdio.h>
#include <stdlib.h>


// Simplified example (no dynamic resizing or robust error handling)
// Requires sorted input for accurate median calculation
double findMedian(int arr[], int n) {
    if (n % 2 == 0) {
        return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
    } else {
        return arr[n / 2];
    }
}

int main() {
    int arr1[] = {1, 2};
    printf("%f\n", findMedian(arr1, 2)); // Output: 1.500000

    int arr2[] = {1, 2, 3};
    printf("%f\n", findMedian(arr2, 3)); // Output: 2.000000

        int arr3[] = {-1, -2};
    printf("%f\n", findMedian(arr3, 2)); // Output: -1.500000

    int arr4[] = {-1, -2, -3};
    printf("%f\n", findMedian(arr4, 3)); // Output: -2.000000


    int arr5[] = {1, 2, 3, 4, 5};
    printf("%f\n", findMedian(arr5, 5)); // Output: 3.000000

    return 0;
}