#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int longestValidParentheses(char * s){
    int maxLen = 0;
    int n = strlen(s);
    int *dp = (int *)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) dp[i] = 0;

    for (int i = 1; i < n; i++) {
        if (s[i] == ')') {
            if (s[i - 1] == '(') {
                dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
            } else if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(') {
                dp[i] = dp[i - 1] + ((i - dp[i - 1] >= 2) ? dp[i - dp[i - 1] - 2] : 0) + 2;
            }
            if(dp[i] > maxLen) maxLen = dp[i];
        }
    }
    free(dp);
    return maxLen;
}

int main() {
    printf("%d\n", longestValidParentheses("(()")); // 2
    printf("%d\n", longestValidParentheses(")()())")); // 4
    printf("%d\n", longestValidParentheses("")); // 0
    printf("%d\n", longestValidParentheses("()(()")); // 2
    printf("%d\n", longestValidParentheses(")(")); // 0
    return 0;
}