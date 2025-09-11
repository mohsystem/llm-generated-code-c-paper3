#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_N 30010
#define MOD 4294967296

typedef long long ll;

int nums[MAX_N];
int n;

int search(int len, int a, ll mod) {
    ll h = 0;
    for (int i = 0; i < len; ++i)
        h = (h * a % mod + nums[i]) % mod;

    ll aL = 1;
    for (int i = 1; i <= len; ++i)
        aL = (aL * a % mod);

    int seen[MOD] = {0};
    for (int start = 0; start < n - len + 1; ++start) {
        if (start != 0) {
            h = (h * a % mod - nums[start - 1] * aL % mod + mod) % mod;
            h = (h + nums[start + len - 1]) % mod;
        }
        if (seen[h])
            return start;
        seen[h] = 1;
    }
    return -1;
}

char* longestDuplicateSubstring(char* s) {
    n = strlen(s);
    for (int i = 0; i < n; ++i)
        nums[i] = (int) s[i] - (int) 'a';

    int a = 26;
    ll mod = (ll) pow(2, 32);
    int left = 1, right = n;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (search(mid, a, mod) != -1)
            left = mid + 1;
        else
            right = mid - 1;
    }

    int start = search(right, a, mod);
    if (start != -1) {
        char* res = (char*) malloc((right + 1) * sizeof(char));
        strncpy(res, s + start, right);
        res[right] = '\0';
        return res;
    }
    return "";
}

int main() {
    printf("%s\n", longestDuplicateSubstring("banana"));  // Output: "ana"
    printf("%s\n", longestDuplicateSubstring("abcd"));  // Output: ""
    return 0;
}