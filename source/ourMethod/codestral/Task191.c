#include <stdio.h>
#include <stdlib.h>

int longestValidParentheses(char *s) {
    int maxLen = 0;
    int stack[30001];
    int top = -1;
    stack[++top] = -1;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            stack[++top] = i;
        } else {
            top--;
            if (top >= 0) {
                maxLen = fmax(maxLen, i - stack[top]);
            } else {
                stack[++top] = i;
            }
        }
    }
    return maxLen;
}

int main() {
    printf("%d\n", longestValidParentheses("(()")); // Output: 2
    printf("%d\n", longestValidParentheses(")()())")); // Output: 4
    printf("%d\n", longestValidParentheses("")); // Output: 0
    printf("%d\n", longestValidParentheses("(")); // Output: 0
    printf("%d\n", longestValidParentheses(")")); // Output: 0
    return 0;
}