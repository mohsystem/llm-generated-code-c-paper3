#include <stdio.h>
#include <string.h>

int longestValidParentheses(const char *s) {
    int maxLength = 0;
    int stack[strlen(s) + 1];
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
                int currentLength = i - stack[top];
                if (currentLength > maxLength) {
                    maxLength = currentLength;
                }
            }
        }
    }

    return maxLength;
}

int main() {
    printf("%d\n", longestValidParentheses("(()"));       // Output: 2
    printf("%d\n", longestValidParentheses(")()())"));    // Output: 4
    printf("%d\n", longestValidParentheses(""));          // Output: 0
    printf("%d\n", longestValidParentheses("()()"));      // Output: 4
    printf("%d\n", longestValidParentheses("(()))("));    // Output: 4
    return 0;
}