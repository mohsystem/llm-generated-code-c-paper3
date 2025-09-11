#include <stdio.h>
#include <math.h>

int digPow(int n, int p) {
    int sum = 0;
    int temp = n;
    int digits[10];
    int length = 0;
    
    while (temp > 0) {
        digits[length++] = temp % 10;
        temp /= 10;
    }
    
    for (int i = length - 1; i >= 0; --i) {
        sum += pow(digits[i], p++);
    }
    
    if (sum % n == 0) {
        return sum / n;
    }
    return -1;
}

int main() {
    printf("%d\n", digPow(89, 1)); // 1
    printf("%d\n", digPow(92, 1)); // -1
    printf("%d\n", digPow(695, 2)); // 2
    printf("%d\n", digPow(46288, 3)); // 51
    printf("%d\n", digPow(46288, 5)); // -1
    return 0;
}