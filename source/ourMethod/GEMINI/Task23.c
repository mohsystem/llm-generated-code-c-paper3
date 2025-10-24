#include <stdio.h>

long long find_nb(long long m) {
    long long n = 0;
    long long remainingVolume = m;
    while (remainingVolume > 0) {
        n++;
        long long cubeVolume = n * n * n;
        remainingVolume -= cubeVolume;
    }

    if (remainingVolume == 0) {
        return n;
    } else {
        return -1;
    }
}

void run_test(long long m, long long expected) {
    long long result = find_nb(m);
    printf("find_nb(%lld) -> %lld (Expected: %lld)\n", m, result, expected);
}

int main() {
    // 5 test cases
    run_test(1071225, 45);
    run_test(91716553919377LL, -1);
    run_test(4183059834009LL, 2022);
    run_test(24723578342962LL, -1);
    run_test(1, 1);
    
    return 0;
}