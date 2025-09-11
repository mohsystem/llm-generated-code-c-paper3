#include<stdio.h>
#include<math.h>

int digPow(int n, int p) {
    int temp = n, sum = 0;
    while (temp > 0) {
        sum += pow(temp % 10, p++);
        temp /= 10;
    }
    return sum % n == 0 ? sum / n : -1;
}

int main() {
    printf("%d\n", digPow(89, 1));  // Output: 1
    printf("%d\n", digPow(92, 1));  // Output: -1
    printf("%d\n", digPow(695, 2)); // Output: 2
    printf("%d\n", digPow(46288, 3)); // Output: 51
    return 0;
}