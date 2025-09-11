#include <stdio.h>
#include <string.h>

char* reverseString(char* s) {
    int n = strlen(s);
    int left = 0, right = n - 1;
    while (left < right) {
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;
        left++;
        right--;
    }
    return s;
}

int main() {
    char testCases[][20] = {"abdcfe", "Hello World", "Geeks for Geeks", "Python", "Reverse"};
    for (int i = 0; i < 5; i++) {
        printf("Input: %s, Output: %s\n", testCases[i], reverseString(testCases[i]));
    }
    return 0;
}