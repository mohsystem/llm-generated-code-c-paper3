#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MIN_VAL (-1000000000LL)
#define MAX_VAL (1000000000LL)
#define MAX_INPUT_LEN (100U)
#define MAX_TOKEN_LEN (32U)

static bool is_upper_alpha(const char* s) {
    size_t len = 0;
    if (s == NULL) return false;
    while (s[len] != '\0') {
        if (len >= 10) return false;
        char c = s[len];
        if (c < 'A' || c > 'Z') return false;
        len++;
    }
    return len >= 1;
}

static bool tokenize3(const char* input, char op[MAX_TOKEN_LEN], char a[MAX_TOKEN_LEN], char b[MAX_TOKEN_LEN]) {
    size_t n = strlen(input);
    if (n == 0 || n > MAX_INPUT_LEN) return false;

    unsigned count = 0;
    unsigned i = 0;
    unsigned w = 0;
    char* targets[3] = { op, a, b };
    unsigned limits[3] = { MAX_TOKEN_LEN, MAX_TOKEN_LEN, MAX_TOKEN_LEN };
    // Initialize outputs
    op[0] = a[0] = b[0] = '\0';

    while (i < n) {
        // skip spaces
        while (i < n && (input[i] == ' ' || input[i] == '\t' || input[i] == '\n' || input[i] == '\r')) i++;
        if (i >= n) break;
        if (count >= 3) {
            // More than 3 tokens -> fail
            return false;
        }
        // read token
        w = 0;
        while (i < n && !(input[i] == ' ' || input[i] == '\t' || input[i] == '\n' || input[i] == '\r')) {
            if (w + 1 >= limits[count]) {
                return false; // token too long
            }
            targets[count][w++] = input[i++];
        }
        targets[count][w] = '\0';
        count++;
    }
    return count == 3;
}

static bool parse_ll(const char* s, long long* out) {
    if (s == NULL || out == NULL) return false;
    size_t len = strlen(s);
    if (len < 1 || len > 20) return false;
    char* end = NULL;
    // Use strtoll with base 10
    long long v = strtoll(s, &end, 10);
    if (end == s || *end != '\0') return false;
    *out = v;
    return true;
}

static bool safe_add(long long a, long long b, long long* out) {
    long long r = a + b;
    if (((a ^ r) & (b ^ r)) < 0) return false;
    *out = r;
    return true;
}

static bool safe_sub(long long a, long long b, long long* out) {
    long long r = a - b;
    if (((a ^ b) & (a ^ r)) < 0) return false;
    *out = r;
    return true;
}

// Robust overflow checks for multiplication
static bool will_mul_overflow(long long a, long long b) {
    if (a == 0 || b == 0) return false;
    if (a == LLONG_MIN && b == -1) return true;
    if (b == LLONG_MIN && a == -1) return true;

    if (a > 0) {
        if (b > 0) {
            return a > LLONG_MAX / b;
        } else { // b < 0
            return b < LLONG_MIN / a;
        }
    } else { // a < 0
        if (b > 0) {
            return a < LLONG_MIN / b;
        } else { // b < 0
            return a < LLONG_MAX / b;
        }
    }
}

static bool safe_mul(long long a, long long b, long long* out) {
    if (will_mul_overflow(a, b)) return false;
    *out = a * b;
    return true;
}

static bool safe_pow(long long base, long long exp, long long* out) {
    long long result = 1;
    long long b = base;
    long long e = exp;
    while (e > 0) {
        if (e & 1LL) {
            if (!safe_mul(result, b, &result)) return false;
        }
        e >>= 1LL;
        if (e) {
            if (!safe_mul(b, b, &b)) return false;
        }
    }
    *out = result;
    return true;
}

char* process_command(const char* input) {
    // Allocate result buffer
    char* res = (char*)malloc(128);
    if (!res) return NULL;
    res[0] = '\0';

    if (input == NULL) {
        snprintf(res, 128, "ERROR: input is null");
        return res;
    }
    size_t inlen = strlen(input);
    if (inlen == 0 || inlen > MAX_INPUT_LEN) {
        snprintf(res, 128, "ERROR: input length out of allowed range (1..100 bytes)");
        return res;
    }

    char op[MAX_TOKEN_LEN];
    char aS[MAX_TOKEN_LEN];
    char bS[MAX_TOKEN_LEN];
    if (!tokenize3(input, op, aS, bS)) {
        snprintf(res, 128, "ERROR: expected format '<OP> <A> <B>' with exactly 3 tokens");
        return res;
    }

    if (!is_upper_alpha(op)) {
        snprintf(res, 128, "ERROR: operation must be uppercase letters only");
        return res;
    }

    bool supported =
        strcmp(op, "ADD") == 0 || strcmp(op, "SUB") == 0 || strcmp(op, "MUL") == 0 ||
        strcmp(op, "DIV") == 0 || strcmp(op, "MOD") == 0 || strcmp(op, "POW") == 0;

    if (!supported) {
        snprintf(res, 128, "ERROR: unsupported operation");
        return res;
    }

    long long a = 0, b = 0;
    if (!parse_ll(aS, &a) || !parse_ll(bS, &b)) {
        snprintf(res, 128, "ERROR: operands must be valid 64-bit integers");
        return res;
    }

    if (a < MIN_VAL || a > MAX_VAL || b < MIN_VAL || b > MAX_VAL) {
        snprintf(res, 128, "ERROR: operands out of allowed range [-1000000000, 1000000000]");
        return res;
    }

    long long result = 0;
    if (strcmp(op, "ADD") == 0) {
        if (!safe_add(a, b, &result)) { snprintf(res, 128, "ERROR: addition overflow"); return res; }
    } else if (strcmp(op, "SUB") == 0) {
        if (!safe_sub(a, b, &result)) { snprintf(res, 128, "ERROR: subtraction overflow"); return res; }
    } else if (strcmp(op, "MUL") == 0) {
        if (!safe_mul(a, b, &result)) { snprintf(res, 128, "ERROR: multiplication overflow"); return res; }
    } else if (strcmp(op, "DIV") == 0) {
        if (b == 0) { snprintf(res, 128, "ERROR: division by zero"); return res; }
        if (a == LLONG_MIN && b == -1) { snprintf(res, 128, "ERROR: division overflow"); return res; }
        result = a / b;
    } else if (strcmp(op, "MOD") == 0) {
        if (b == 0) { snprintf(res, 128, "ERROR: modulo by zero"); return res; }
        result = a % b;
    } else if (strcmp(op, "POW") == 0) {
        if (b < 0) { snprintf(res, 128, "ERROR: negative exponent not supported"); return res; }
        if (b > 62) { snprintf(res, 128, "ERROR: exponent too large"); return res; }
        if (!safe_pow(a, b, &result)) { snprintf(res, 128, "ERROR: power overflow"); return res; }
    } else {
        snprintf(res, 128, "ERROR: unsupported operation");
        return res;
    }

    snprintf(res, 128, "OK result: %lld", result);
    return res;
}

int main(void) {
    const char* tests[5] = {
        "ADD 3 5",
        "DIV 10 0",
        "MUL 123456 789",
        "POW 2 10",
        "XYZ 1 2"
    };
    for (int i = 0; i < 5; i++) {
        char* out = process_command(tests[i]);
        if (out) {
            printf("Input: '%s' -> %s\n", tests[i], out);
            free(out);
        } else {
            printf("Input: '%s' -> ERROR: unexpected failure\n", tests[i]);
        }
    }
    return 0;
}