#include <stdio.h>
#include <string.h>

void reverseString(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}


int main() {
    char str1[] = "hello";
    reverseString(str1);
    printf("%s\n", str1);

    char str2[] = "world";
    reverseString(str2);
    printf("%s\n", str2);

    char str3[] = "";
    reverseString(str3);
    printf("%s\n", str3);

    char str4[] = "12345";
    reverseString(str4);
    printf("%s\n", str4);

    char str5[] = "racecar";
    reverseString(str5);
    printf("%s\n", str5);

    return 0;
}