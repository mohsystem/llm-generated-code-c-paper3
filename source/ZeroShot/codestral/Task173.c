#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 30010
#define MOD 1000000007

typedef unsigned long long ull;

struct HashSet {
    ull values[MAX_SIZE];
    int size;
};

void initHashSet(struct HashSet* set) {
    set->size = 0;
}

bool contains(struct HashSet* set, ull value) {
    for (int i = 0; i < set->size; i++) {
        if (set->values[i] == value) {
            return true;
        }
    }
    return false;
}

void add(struct HashSet* set, ull value) {
    set->values[set->size++] = value;
}

char* longestDupSubstring(char* s) {
    int n = strlen(s);
    int* nums = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        nums[i] = s[i] - 'a';
    }

    int a = 26;
    ull mod = 1e9 + 7;
    ull aL = 1;
    for (int i = 1; i < n; i++) {
        aL = (aL * a) % mod;
    }

    int left = 1, right = n;
    int start = -1, length = 0;
    while (left <= right) {
        int len = left + (right - left) / 2;
        ull h = 0;
        struct HashSet set;
        initHashSet(&set);
        for (int i = 0; i < len; i++) {
            h = (h * a + nums[i]) % mod;
        }
        if (!contains(&set, h)) {
            add(&set, h);
            right = len - 1;
        } else {
            left = len + 1;
            start = len;
        }

        for (int i = len; i < n; i++) {
            h = (h * a - nums[i - len] * aL % mod + mod) % mod;
            h = (h + nums[i]) % mod;
            if (!contains(&set, h)) {
                add(&set, h);
                continue;
            }
            start = i - len + 1;
            length = len;
            break;
        }
    }

    if (start == -1) {
        return "";
    }
    char* result = (char*)malloc((length + 1) * sizeof(char));
    strncpy(result, s + start, length);
    result[length] = '\0';
    free(nums);
    return result;
}

int main() {
    printf("%s\n", longestDupSubstring("banana")); // "ana"
    printf("%s\n", longestDupSubstring("abcd")); // ""
    printf("%s\n", longestDupSubstring("abcabcabc")); // "abc"
    printf("%s\n", longestDupSubstring("aaaaaa")); // "aaaaa"
    printf("%s\n", longestDupSubstring("abababab")); // "abab"
    return 0;
}