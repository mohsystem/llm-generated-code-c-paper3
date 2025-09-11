#include <stdio.h>
#include <string.h>

void reverseString(char* s) {
    int length = strlen(s);
    int left = 0, right = length - 1;
    while (left < right) {
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;
        left++;
        right--;
    }
}

int main() {
    char testCases[][10] = {"abdcfe", "hello", "world", "reverse", "test"};
    for (int i = 0; i < 5; i++) {
        char original[10];
        strcpy(original, testCases[i]);
        reverseString(testCases[i]);
        printf("Original: %s, Reversed: %s\n", original, testCases[i]);
    }
    return 0;
}