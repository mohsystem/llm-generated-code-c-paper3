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
    char testCases[][20] = {"Hello World", "C", "Python", "Java", "Reverse Me"};
    for (int i = 0; i < 5; i++) {
        printf("Original: %s, Reversed: %s\n", testCases[i], reverseString(testCases[i]));
    }
    return 0;
}