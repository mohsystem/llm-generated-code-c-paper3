#include <stdio.h>
#include <string.h>

int longestValidParentheses(const char* s) {
    int maxLen = 0;
    int len = strlen(s);
    int* dp = (int*)malloc((len + 1) * sizeof(int));
    for (int i = 0; i <= len; i++) {
        dp[i] = 0;
    }
    for (int i = 1; i <= len; i++) {
        if (s[i - 1] == ')') {
            if (i >= 2 && s[i - 2] == '(') {
                dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
            } else if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(') {
                dp[i] = dp[i - 1] + (i - dp[i - 1] >= 2 ? dp[i - dp[i - 1] - 2] : 0) + 2;
            }
            maxLen = (maxLen > dp[i] ? maxLen : dp[i]);
        }
    }
    free(dp);
    return maxLen;
}

int main() {
    printf("%d\n", longestValidParentheses("(()")); // Output: 2
    printf("%d\n", longestValidParentheses(")()())")); // Output: 4
    printf("%d\n", longestValidParentheses("")); // Output: 0
    return 0;
}