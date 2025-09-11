#include<stdio.h>
#include<math.h>

int digPow(int n, int p) {
    int originalNumber = n;
    int sum = 0;
    while (n > 0) {
        int digit = n % 10;
        sum += pow(digit, p);
        n /= 10;
        p++;
    }
    if (sum % originalNumber == 0) {
        return sum / originalNumber;
    } else {
        return -1;
    }
}

int main() {
    printf("%d\n", digPow(89, 1)); // 1
    printf("%d\n", digPow(92, 1)); // -1
    printf("%d\n", digPow(695, 2)); // 2
    printf("%d\n", digPow(46288, 3)); // 51
    return 0;
}