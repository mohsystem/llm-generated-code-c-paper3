#include <stdio.h>
#include <string.h>

int longestValidParentheses(const char* s) {
    int maxLength = 0;
    int left = 0, right = 0;
    int n = strlen(s);
    
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            left++;
        } else {
            right++;
        }
        if (left == right) {
            if (maxLength < 2 * right) {
                maxLength = 2 * right;
            }
        } else if (right > left) {
            left = right = 0;
        }
    }
    
    left = right = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '(') {
            left++;
        } else {
            right++;
        }
        if (left == right) {
            if (maxLength < 2 * left) {
                maxLength = 2 * left;
            }
        } else if (left > right) {
            left = right = 0;
        }
    }
    
    return maxLength;
}

int main() {
    printf("%d\n", longestValidParentheses("(()")); // 2
    printf("%d\n", longestValidParentheses(")()())")); // 4
    printf("%d\n", longestValidParentheses("")); // 0
    printf("%d\n", longestValidParentheses("()(()")); // 2
    printf("%d\n", longestValidParentheses("()()")); // 4
    return 0;
}