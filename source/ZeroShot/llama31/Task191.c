#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestValidParentheses(char* s) {
    int maxLen = 0;
    int* stack = (int*)malloc((strlen(s) + 1) * sizeof(int));
    int top = 0;
    stack[top++] = -1;
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == '(') {
            stack[top++] = i;
        } else {
            top--;
            if (top == 0) {
                stack[top++] = i;
            } else {
                maxLen = (maxLen > i - stack[top - 1]) ? maxLen : i - stack[top - 1];
            }
        }
    }
    free(stack);
    return maxLen;
}

int main() {
    printf("%d\n", longestValidParentheses("(()")); // Output: 2
    printf("%d\n", longestValidParentheses(")()())")); // Output: 4
    printf("%d\n", longestValidParentheses("")); // Output: 0
    printf("%d\n", longestValidParentheses("((())")); // Output: 4
    printf("%d\n", longestValidParentheses(")()()(")); // Output: 4
    return 0;
}