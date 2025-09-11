#include <stdio.h>
#include <string.h>

int longestValidParentheses(char *s) {
    int maxLen = 0, left = 0, right = 0;
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == '(') {
            left++;
        } else {
            right++;
        }
        if (left == right) {
            maxLen = (maxLen > 2 * right) ? maxLen : 2 * right;
        } else if (right > left) {
            left = right = 0;
        }
    }
    left = right = 0;
    for (int i = strlen(s) - 1; i >= 0; i--) {
        if (s[i] == '(') {
            left++;
        } else {
            right++;
        }
        if (left == right) {
            maxLen = (maxLen > 2 * left) ? maxLen : 2 * left;
        } else if (left > right) {
            left = right = 0;
        }
    }
    return maxLen;
}

int main() {
    printf("%d\n", longestValidParentheses("(()"));  // Output: 2
    printf("%d\n", longestValidParentheses(")()())"));  // Output: 4
    printf("%d\n", longestValidParentheses(""));  // Output: 0
    return 0;
}