#include <stdio.h>
#include <string.h>

void reverseString(char* s) {
    int len = strlen(s);
    for (int i = 0; i < len / 2; i++) {
        char temp = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = temp;
    }
}

int main() {
    char str1[] = "Hello, World!";
    char str2[] = "12345";
    char str3[] = "racecar";
    char str4[] = "";
    char str5[] = "a";

    reverseString(str1);
    reverseString(str2);
    reverseString(str3);
    reverseString(str4);
    reverseString(str5);

    printf("%s\n", str1);
    printf("%s\n", str2);
    printf("%s\n", str3);
    printf("%s\n", str4);
    printf("%s\n", str5);

    return 0;
}