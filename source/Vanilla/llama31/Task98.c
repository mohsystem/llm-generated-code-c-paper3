#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convertToInt(const char* s) {
    int num = 0;
    int n = strlen(s);
    int sign = 1;
    int i = 0;

    if (s[0] == '-') {
        sign = -1;
        i++;
    } else if (s[0] == '+') {
        i++;
    }

    for (; i < n; i++) {
        if (s[i] < '0' || s[i] > '9') {
            fprintf(stderr, "Invalid input\n");
            exit(EXIT_FAILURE);
        }
        num = num * 10 + (s[i] - '0');
    }

    return num * sign;
}

int main() {
    const char* testCases[] = {"123", "456", "-789", "abc", "123.45"};
    for (int i = 0; i < 5; i++) {
        int result = convertToInt(testCases[i]);
        printf("%d\n", result);
    }
    return 0;
}