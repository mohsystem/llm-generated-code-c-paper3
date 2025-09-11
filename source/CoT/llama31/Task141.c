#include <stdio.h>
#include <string.h>

char* reverseString(char* s) {
    int length = strlen(s);
    char* res = s;
    int left = 0, right = length - 1;
    while (left < right) {
        char temp = res[left];
        res[left] = res[right];
        res[right] = temp;
        left++;
        right--;
    }
    return res;
}

int main() {
    char testCases[][20] = {"abdcfe", "Hello World", "Geeks for Geeks", "Python", "Java"};
    for (int i = 0; i < 5; i++) {
        printf("Input: %s, Output: %s\n", testCases[i], reverseString(testCases[i]));
    }
    return 0;
}