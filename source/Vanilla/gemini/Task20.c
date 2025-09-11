#include <stdio.h>
#include <math.h>

long long digPow(int n, int p) {
    int digits[10]; // Assuming max 10 digits
    int temp = n;
    int count = 0;
    while (temp > 0) {
        digits[count++] = temp % 10;
        temp /= 10;
    }

    long long sum = 0;
    for (int i = 0; i < count; i++) {
        sum += pow(digits[count - 1 - i], p + i);
    }

    if (sum % n == 0) {
        return sum / n;
    } else {
        return -1;
    }
}

int main() {
    printf("%lld\n", digPow(89, 1)); // 1
    printf("%lld\n", digPow(92, 1)); // -1
    printf("%lld\n", digPow(695, 2)); // 2
    printf("%lld\n", digPow(46288, 3)); // 51
    printf("%lld\n", digPow(46288, 5)); // -1

    return 0;
}