
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestValidParentheses(char* s) {
    if(!s || strlen(s) == 0) return 0;
    
    int len = strlen(s);
    int* dp = (int*)calloc(len, sizeof(int));
    int maxLen = 0;
    
    for(int i = 1; i < len; i++) {
        if(s[i] == ')') {
            if(s[i-1] == '(') {
                dp[i] = (i >= 2 ? dp[i-2] : 0) + 2;
            }
            else if(i - dp[i-1] > 0 && s[i - dp[i-1] - 1] == '(') {
                dp[i] = dp[i-1] + 2 + ((i - dp[i-1] >= 2) ? dp[i-dp[i-1]-2] : 0);
            }
            maxLen = maxLen > dp[i] ? maxLen : dp[i];
        }
    }
    
    free(dp);
    return maxLen;
}

int main() {
    // Test cases
    printf("%d\\n", longestValidParentheses("(()"));  // 2
    printf("%d\\n", longestValidParentheses(")()())"));  // 4
    printf("%d\\n", longestValidParentheses(""));  // 0
    printf("%d\\n", longestValidParentheses("()(()"));  // 2
    printf("%d\\n", longestValidParentheses("(()())"));  // 6
    return 0;
}
