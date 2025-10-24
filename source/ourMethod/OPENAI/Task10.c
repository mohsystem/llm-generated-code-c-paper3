#include <stdio.h>

long long get_sum(long long a, long long b) {
    long long start = (a < b) ? a : b;
    long long end = (a > b) ? a : b;
    long long n = (end - start) + 1;     // number of terms
    long long sumPair = start + end;     // first + last
    if ((n & 1LL) == 0LL) {
        return (n / 2LL) * sumPair;      // n is even
    } else {
        return n * (sumPair / 2LL);      // sumPair is even
    }
}

int main(void) {
    long long tests[5][2] = {
        {1, 0},
        {1, 2},
        {0, 1},
        {1, 1},
        {-1, 2}
    };
    for (int i = 0; i < 5; ++i) {
        long long a = tests[i][0];
        long long b = tests[i][1];
        long long res = get_sum(a, b);
        printf("%lld\n", res);
    }
    return 0;
}