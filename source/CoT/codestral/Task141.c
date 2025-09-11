#include <stdio.h>
#include <string.h>

void reverseString(char* input) {
    int length = strlen(input);
    for (int i = 0; i < length / 2; i++) {
        char temp = input[i];
        input[i] = input[length - i - 1];
        input[length - i - 1] = temp;
    }
}

int main() {
    char str1[] = "Hello, World!";
    reverseString(str1);
    printf("%s\n", str1); // !dlroW ,olleH

    char str2[] = "12345";
    reverseString(str2);
    printf("%s\n", str2); // 54321

    char str3[] = "";
    reverseString(str3);
    printf("%s\n", str3); // empty string

    char str4[] = "a";
    reverseString(str4);
    printf("%s\n", str4); // a

    char str5[] = "ab";
    reverseString(str5);
    printf("%s\n", str5); // ba

    return 0;
}