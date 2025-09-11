#include <stdio.h>
#include <math.h>
#include <string.h>

int findK(int n, int p) {
    char digits[12]; 
    sprintf(digits, "%d", n);
    int sum = 0;
    int length = strlen(digits);
    
    for (int i = 0; i < length; ++i) {
        sum += pow(digits[i] - '0', p + i);
    }
    
    return (sum % n == 0) ? sum / n : -1;
}

int main() {
    printf("%d\n", findK(89, 1));    // Output: 1
    printf("%d\n", findK(92, 1));    // Output: -1
    printf("%d\n", findK(695, 2));   // Output: 2
    printf("%d\n", findK(46288, 3)); // Output: 51
    printf("%d\n", findK(10, 1));    // Output: -1
    return 0;
}