#include <stdio.h>
#include <string.h>

void reverse_string(char *str) {
    int len = strlen(str);
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

int main() {
    char str1[] = "hello";
    reverse_string(str1);
    printf("%s\n", str1);

    char str2[] = "world";
    reverse_string(str2);
    printf("%s\n", str2);

    char str3[] = "racecar";
    reverse_string(str3);
    printf("%s\n", str3);

    char str4[] = "apple";
    reverse_string(str4);
    printf("%s\n", str4);

    char str5[] = "";
    reverse_string(str5);
    printf("%s\n", str5);

    return 0;
}