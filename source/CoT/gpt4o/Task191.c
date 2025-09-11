#include <stdio.h>
#include <string.h>

int longestValidParentheses(const char* s) {
    int maxLen = 0;
    int left = 0, right = 0;
    int length = strlen(s);

    // Traverse from left to right
    for (int i = 0; i < length; i++) {
        if (s[i] == '(') {
            left++;
        } else {
            right++;
        }

        if (left == right) {
            if (maxLen < 2 * right) {
                maxLen = 2 * right;
            }
        } else if (right > left) {
            left = right = 0;
        }
    }

    left = right = 0;

    // Traverse from right to left
    for (int i = length - 1; i >= 0; i--) {
        if (s[i] == '(') {
            left++;
        } else {
            right++;
        }

        if (left == right) {
            if (maxLen < 2 * left) {
                maxLen = 2 * left;
            }
        } else if (left > right) {
            left = right = 0;
        }
    }

    return maxLen;
}

int main() {
    printf("%d\n", longestValidParentheses("(()")); // Output: 2
    printf("%d\n", longestValidParentheses(")()())")); // Output: 4
    printf("%d\n", longestValidParentheses("")); // Output: 0
    printf("%d\n", longestValidParentheses("()(()")); // Output: 2
    printf("%d\n", longestValidParentheses("()(())")); // Output: 6

    return 0;
}