#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

char *longestDupSubstring(char *s) {
    int n = strlen(s);
    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = (int) s[i] - (int) 'a';
    }
    int left = 1, right = n;
    while (left < right) {
        int mid = left + (right - left) / 2;
        int *start = (int *)malloc(sizeof(int));
        *start = -1;
        search(arr, n, mid, MOD, start);
        if (*start != -1) {
            left = mid + 1;
        } else {
            right = mid;
        }
        free(start);
    }
    int *start = (int *)malloc(sizeof(int));
    *start = -1;
    search(arr, n, left - 1, MOD, start);
    if (*start != -1) {
        char *result = (char *)malloc(sizeof(char) * (left + 1));
        strncpy(result, s + *start, left);
        result[left] = '\0';
        free(start);
        return result;
    }
    free(start);
    return "";
}

void search(int arr[], int n, int len, int mod, int *start) {
    long h = 0;
    for (int i = 0; i < len; i++) {
        h = (h * 26 + arr[i]) % mod;
    }
    long aL = 1;
    for (int i = 1; i <= len; i++) {
        aL = (aL * 26) % mod;
    }
    int *seen = (int *)calloc(mod, sizeof(int));
    seen[h] = 1;
    for (int i = 1; i <= n - len; i++) {
        h = (h * 26 - arr[i - 1] * aL % mod + mod + arr[i + len - 1]) % mod;
        if (seen[h]) {
            *start = i;
            free(seen);
            return;
        }
        seen[h] = 1;
    }
    free(seen);
}

int main() {
    char *s1 = "banana";
    char *result1 = longestDupSubstring(s1);
    printf("%s\n", result1);  // Output: "ana"
    free(result1);

    char *s2 = "abcd";
    char *result2 = longestDupSubstring(s2);
    printf("%s\n", result2);  // Output: ""
    free(result2);

    return 0;
}