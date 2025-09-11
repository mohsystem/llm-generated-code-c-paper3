#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int longestValidParentheses(char * s) {
    int maxLen = 0;
    int *stack = (int *)malloc(sizeof(int) * (strlen(s) + 1));
    int top = -1;
    stack[++top] = -1;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            stack[++top] = i;
        } else {
            top--;
            if (top == -1) {
                stack[++top] = i;
            } else {
                maxLen = (maxLen > (i - stack[top])) ? maxLen : (i - stack[top]);
            }
        }
    }
    free(stack);
    return maxLen;
}

int main() {
    printf("%d\n", longestValidParentheses("(()")); // 2
    printf("%d\n", longestValidParentheses(")()())")); // 4
    printf("%d\n", longestValidParentheses("")); // 0
    printf("%d\n", longestValidParentheses("()(()")); // 2
    printf("%d\n", longestValidParentheses(")()())()()(")); // 6
    return 0;
}