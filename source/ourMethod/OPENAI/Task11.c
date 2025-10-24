#include <stdio.h>
#include <math.h>
#include <float.h>

int nb_year(long long p0, double percent, long long aug, long long p) {
    if (p0 <= 0 || p <= 0 || percent < 0.0 || !isfinite(percent)) {
        return -1;
    }
    if (p0 >= p) {
        return 0;
    }
    if (percent == 0.0 && aug <= 0) {
        return -1;
    }

    long long current = p0;
    int years = 0;
    const int MAX_YEARS = 10000000;

    while (current < p) {
        if (years >= MAX_YEARS) {
            return -1;
        }
        long long growth = (long long)floor(current * (percent / 100.0));
        long long next = current + growth + aug;
        if (next < 0) {
            next = 0;
        }
        if (next == current) {
            return -1; // Stuck, cannot progress further
        }
        current = next;
        years++;
    }
    return years;
}

int main(void) {
    // 5 test cases
    printf("%d\n", nb_year(1000LL, 2.0, 50LL, 1200LL));            // Expected 3
    printf("%d\n", nb_year(1500LL, 5.0, 100LL, 5000LL));           // Expected 15
    printf("%d\n", nb_year(1500000LL, 2.5, 10000LL, 2000000LL));   // Expected 10
    printf("%d\n", nb_year(1000LL, 0.0, 0LL, 1000LL));             // Expected 0
    printf("%d\n", nb_year(1000LL, 0.0, -1LL, 1200LL));            // Expected -1 (unreachable)
    return 0;
}