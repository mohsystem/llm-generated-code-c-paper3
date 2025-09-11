#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MOD 1000000007
#define P 31

int search(char* s, int len) {
    long h = 0;
    long* pow = (long*)malloc(len * sizeof(long));
    pow[0] = 1;
    for (int i = 1; i < len; i++) {
        pow[i] = pow[i - 1] * P % MOD;
    }
    for (int i = 0; i < len; i++) {
        h = (h * P + s[i]) % MOD;
    }
    int* seen = (int*)calloc(MOD, sizeof(int));
    seen[h] = 1;
    for (int i = len; i < strlen(s); i++) {
        h = (h * P - s[i - len] * pow[len - 1] % MOD + MOD) % MOD;
        h = (h + s[i]) % MOD;
        if (seen[h]) {
            return i - len + 1;
        }
        seen[h] = 1;
    }
    free(pow);
    free(seen);
    return -1;
}

char* longestDupSubstring(char* s) {
    int n = strlen(s);
    int left = 1, right = n;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (search(s, mid) != -1) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    int start = search(s, left - 1);
    if (start != -1) {
        char* result = (char*)malloc((left - 1) * sizeof(char));
        strncpy(result, s + start, left - 1);
        result[left - 1] = '\0';
        return result;
    }
    return "";
}

int main() {
    printf("%s\n", longestDupSubstring("banana")); // Output: "ana"
    printf("%s\n", longestDupSubstring("abcd")); // Output: ""
    return 0;
}