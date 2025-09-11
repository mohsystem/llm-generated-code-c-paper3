#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000009

int search(int length, int* nums, int mod) {
    long long h = 1;
    for (int i = 0; i < length; i++) {
        h = (h * 26) % mod;
    }
    long long hash = 0;
    for (int i = 0; i < length; i++) {
        hash = (hash * 26 + nums[i]) % mod;
    }
    int* seen = (int*)calloc(length, sizeof(int));
    seen[0] = 0;
    for (int start = 1; start < length; start++) {
        hash = (hash - h * nums[start - 1] % mod + mod) % mod;
        hash = (hash * 26 + nums[start + length - 1]) % mod;
        for (int j = 0; j < start; j++) {
            if (hash == seen[j]) {
                free(seen);
                return j;
            }
        }
        seen[start] = hash;
    }
    free(seen);
    return -1;
}

char* longestDupSubstring(char* s) {
    int n = strlen(s);
    int* nums = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        nums[i] = s[i] - 'a';
    }
    int mod = MOD;
    int low = 0, high = n;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (search(mid, nums, mod) != -1) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    int pos = search(low - 1, nums, mod);
    char* result = (char*)malloc((low - 1 + 1) * sizeof(char));
    strncpy(result, s + pos, low - 1);
    result[low - 1] = '\0';
    free(nums);
    return result;
}

int main() {
    char s1[] = "banana";
    char s2[] = "abcd";
    char s3[] = "abcabc";
    char s4[] = "aabbcc";
    char s5[] = "ababab";

    printf("%s\n", longestDupSubstring(s1)); // "ana"
    printf("%s\n", longestDupSubstring(s2)); // ""
    printf("%s\n", longestDupSubstring(s3)); // "abc"
    printf("%s\n", longestDupSubstring(s4)); // "bb"
    printf("%s\n", longestDupSubstring(s5)); // "abab"

    return 0;
}