#include <stdio.h>
#include <stddef.h>

static int is_upper(char c) { return c >= 'A' && c <= 'Z'; }
static int is_lower(char c) { return c >= 'a' && c <= 'z'; }
static int is_letter(char c) { return is_upper(c) || is_lower(c); }

char find_missing_letter(const char *arr, size_t len) {
    if (arr == NULL || len < 2) {
        return '\0';
    }

    char first = arr[0];
    if (!is_letter(first)) {
        return '\0';
    }
    int upper = is_upper(first);
    char prev = first;

    for (size_t i = 0; i < len; i++) {
        char c = arr[i];
        if (!is_letter(c)) {
            return '\0';
        }
        if (upper) {
            if (!is_upper(c)) return '\0';
        } else {
            if (!is_lower(c)) return '\0';
        }

        if (i > 0) {
            if (c <= prev) {
                return '\0';
            }
            int diff = (int)c - (int)prev;
            if (diff > 1) {
                char miss = (char)(prev + 1);
                if (!is_letter(miss)) return '\0';
                if (upper && !is_upper(miss)) return '\0';
                if (!upper && !is_lower(miss)) return '\0';
                return miss;
            }
        }
        prev = c;
    }

    int candidate_val = (int)arr[0] + (int)len;
    char candidate = (char)candidate_val;
    if (!is_letter(candidate)) return '\0';
    if (upper) {
        if (!is_upper(candidate)) return '\0';
    } else {
        if (!is_lower(candidate)) return '\0';
    }
    return candidate;
}

int main(void) {
    char arr1[] = {'a','b','c','d','f'};
    char arr2[] = {'O','Q','R','S'};
    char arr3[] = {'g','h','j','k'};
    char arr4[] = {'A','B','C','E'};
    char arr5[] = {'t','u','v','x'};

    char res1 = find_missing_letter(arr1, sizeof(arr1)/sizeof(arr1[0]));
    char res2 = find_missing_letter(arr2, sizeof(arr2)/sizeof(arr2[0]));
    char res3 = find_missing_letter(arr3, sizeof(arr3)/sizeof(arr3[0]));
    char res4 = find_missing_letter(arr4, sizeof(arr4)/sizeof(arr4[0]));
    char res5 = find_missing_letter(arr5, sizeof(arr5)/sizeof(arr5[0]));

    printf("Test 1: %c\n", res1);
    printf("Test 2: %c\n", res2);
    printf("Test 3: %c\n", res3);
    printf("Test 4: %c\n", res4);
    printf("Test 5: %c\n", res5);

    return 0;
}