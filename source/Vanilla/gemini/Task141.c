#include <stdio.h>
#include <string.h>

void reverse_string(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

int main() {
    char str1[] = "hello";
    reverse_string(str1);
    printf("%s\n", str1); // olleh

    char str2[] = "world";
    reverse_string(str2);
    printf("%s\n", str2); // dlrow

    char str3[] = "racecar";
    reverse_string(str3);
    printf("%s\n", str3); // racecar

    char str4[] = "madam";
    reverse_string(str4);
    printf("%s\n", str4); // madam

    char str5[] = "";
    reverse_string(str5);
    printf("%s\n", str5); // 

    return 0;
}