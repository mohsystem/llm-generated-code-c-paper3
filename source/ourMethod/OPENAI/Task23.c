#include <stdio.h>
#include <limits.h>

static long long isqrt(long long x) {
    if (x < 0) return -1;
    long long lo = 0;
    long long hi = x < 3037000500LL ? x : 3037000500LL; // floor(sqrt(LLONG_MAX))
    long long ans = 0;
    while (lo <= hi) {
        long long mid = lo + ((hi - lo) >> 1);
        if (mid == 0) {
            ans = 0;
            lo = 1;
            continue;
        }
        if (mid <= x / mid) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return ans;
}

static long long triFromN(long long n) {
    if ((n & 1LL) == 0) {
        return (n / 2LL) * (n + 1LL);
    } else {
        return n * ((n + 1LL) / 2LL);
    }
}

long long findNb(long long m) {
    if (m < 0) return -1;
    if (m == 0) return 0;

    long long s = isqrt(m);
    if (s < 0 || s * s != m) return -1;

    long long disc = 1 + 8LL * s;
    long long r = isqrt(disc);
    if (r < 0 || r * r != disc) return -1;

    long long n = (r - 1LL) / 2LL;
    if (triFromN(n) == s) return n;
    return -1;
}

int main(void) {
    long long tests[5] = {
        1071225LL,          // expected 45
        91716553919377LL,   // expected -1
        1LL,                // expected 1
        4183059834009LL,    // expected 2022
        0LL                 // expected 0
    };
    for (int i = 0; i < 5; ++i) {
        printf("%lld\n", findNb(tests[i]));
    }
    return 0;
}