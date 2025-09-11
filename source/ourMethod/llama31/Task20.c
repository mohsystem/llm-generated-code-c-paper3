#include <stdio.h>
#include <string.h>
#include <math.h>

int findK(int n, int p) {
    // Convert n to a string to easily access its digits
    char strN[20];
    sprintf(strN, "%d", n);
    long long sum = 0;
    for (int i = 0; i < strlen(strN); i++) {
        // Calculate the power and add to the sum
        sum += (long long) pow(strN[i] - '0', p + i);
    }
    // Check if the sum is a multiple of n
    if (sum % n == 0) {
        return sum / n;
    } else {
        return -1;
    }
}

int main() {
    // Test cases
    printf("%d\n", findK(89, 1));   // Expected: 1
    printf("%d\n", findK(92, 1));   // Expected: -1
    printf("%d\n", findK(695, 2));  // Expected: 2
    printf("%d\n", findK(46288, 3)); // Expected: 51
    printf("%d\n", findK(123, 2));  // Expected: -1
    return 0;
}