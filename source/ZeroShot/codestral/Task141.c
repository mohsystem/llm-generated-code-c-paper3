#include <stdio.h>
#include <string.h>

void reverseString(char* input) {
    int len = strlen(input);
    for (int i = 0; i < len / 2; i++) {
        char temp = input[i];
        input[i] = input[len - i - 1];
        input[len - i - 1] = temp;
    }
}

int main() {
    char str1[] = "Hello";
    reverseString(str1);
    printf("%s\n", str1); // olleH

    char str2[] = "World";
    reverseString(str2);
    printf("%s\n", str2); // dlroW

    char str3[] = "12345";
    reverseString(str3);
    printf("%s\n", str3); // 54321

    char str4[] = "";
    reverseString(str4);
    printf("%s\n", str4); //

    char str5[] = "a";
    reverseString(str5);
    printf("%s\n", str5); // a

    return 0;
}