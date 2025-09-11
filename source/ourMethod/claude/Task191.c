
#include <stdio.h>
#include <string.h>

int longestValidParentheses(const char* s) {
    if (!s || strlen(s) < 2) {
        return 0;
    }
    
    int len = strlen(s);
    int dp[30001] = {0};  // Max length constraint is 3*10^4
    int maxLength = 0;
    
    for (int i = 1; i < len; i++) {
        if (s[i] == ')') {
            if (s[i-1] == '(') {
                dp[i] = (i >= 2 ? dp[i-2] : 0) + 2;
            }
            else if (i - dp[i-1] > 0 && s[i - dp[i-1] - 1] == '(') {
                dp[i] = dp[i-1] + 2;
                if (i - dp[i-1] >= 2) {
                    dp[i] += dp[i - dp[i-1] - 2];
                }
            }
            if (dp[i] > maxLength) {
                maxLength = dp[i];
            }
        }
    }
    return maxLength;
}

int main() {
    // Test cases
    printf("%d\\n", longestValidParentheses("(()"));      // Expected: 2
    printf("%d\\n", longestValidParentheses(")()())"));   // Expected: 4
    printf("%d\\n", longestValidParentheses(""));         // Expected: 0
    printf("%d\\n", longestValidParentheses("()(()"));    // Expected: 2
    printf("%d\\n", longestValidParentheses("(()())"));   // Expected: 6
    return 0;
}
