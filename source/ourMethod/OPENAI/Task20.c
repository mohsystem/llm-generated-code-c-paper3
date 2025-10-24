#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

static bool safe_mul_u64(uint64_t a, uint64_t b, uint64_t *out) {
    if (out == NULL) return false;
    if (a == 0 || b == 0) { *out = 0; return true; }
    if (a > UINT64_MAX / b) return false;
    *out = a * b;
    return true;
}

static bool safe_pow_u64(uint64_t base, unsigned int exp, uint64_t *out) {
    if (out == NULL) return false;
    uint64_t result = 1;
    for (unsigned int i = 0; i < exp; ++i) {
        if (!safe_mul_u64(result, base, &result)) {
            return false;
        }
    }
    *out = result;
    return true;
}

long long dig_pow(unsigned long long n, unsigned int p) {
    if (n == 0ULL || p == 0U) return -1LL;
    char buf[32];
    int nw = snprintf(buf, sizeof(buf), "%llu", (unsigned long long)n);
    if (nw <= 0 || nw >= (int)sizeof(buf)) return -1LL;

    unsigned __int128 sum = 0;
    unsigned int exp = p;
    for (int i = 0; buf[i] != '\0'; ++i) {
        char ch = buf[i];
        if (ch < '0' || ch > '9') return -1LL;
        uint64_t d = (uint64_t)(ch - '0');
        uint64_t powv = 0;
        if (!safe_pow_u64(d, exp, &powv)) {
            return -1LL;
        }
        sum += (unsigned __int128)powv;
        ++exp;
    }
    if ((unsigned long long)(sum % (unsigned __int128)n) != 0ULL) {
        return -1LL;
    }
    unsigned __int128 k128 = sum / (unsigned __int128)n;
    if (k128 > (unsigned __int128)LLONG_MAX) return -1LL;
    return (long long)k128;
}

int main(void) {
    struct { unsigned long long n; unsigned int p; } tests[5] = {
        {89ULL, 1U},
        {92ULL, 1U},
        {695ULL, 2U},
        {46288ULL, 3U},
        {1ULL, 1U}
    };
    for (int i = 0; i < 5; ++i) {
        long long res = dig_pow(tests[i].n, tests[i].p);
        printf("dig_pow(%llu, %u) = %lld\n",
               (unsigned long long)tests[i].n,
               (unsigned int)tests[i].p,
               (long long)res);
    }
    return 0;
}