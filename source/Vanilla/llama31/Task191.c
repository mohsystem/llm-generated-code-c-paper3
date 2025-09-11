#include <stdio.h>
#include <string.h>

int longestValidParentheses(char *s) {
    int n = strlen(s);
    int dp[n + 1];
    int maxLen = 0;
    for (int i = 0; i <= n; i++) {
        dp[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        if (s[i - 1] == ')') {
            if (s[i - 2] == '(') {
                dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
            } else if (i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 2] == '(') {
                dp[i] = dp[i - 1] + (i - dp[i - 1] - 2 >= 0 ? dp[i - dp[i - 1] - 2] : 0) + 2;
            }
            maxLen = (maxLen > dp[i] ? maxLen : dp[i]);
        }
    }
    return maxLen;
}

int main() {
    printf("%d\n", longestValidParentheses("(()")); // Output: 2
    printf("%d\n", longestValidParentheses(")()())")); // Output: 4
    printf("%d\n", longestValidParentheses("")); // Output: 0
    printf("%d\n", longestValidParentheses("((())")); // Output: 4
    printf("%d\n", longestValidParentheses(")()()")); // Output: 6
    return 0;
}