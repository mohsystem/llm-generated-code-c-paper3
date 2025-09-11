#include <stdio.h>
#include <string.h>

void tweakLetters(char* str, int tweaks[], int len) {
    for (int i = 0; i < len; i++) {
        str[i] = (char) (str[i] + tweaks[i]);
    }
}

int main() {
    char str1[] = "apple";
    int tweaks1[] = {0, 1, -1, 0, -1};
    tweakLetters(str1, tweaks1, 5);
    printf("%s\n", str1); // "aqold"

    char str2[] = "many";
    int tweaks2[] = {0, 0, 0, -1};
    tweakLetters(str2, tweaks2, 4);
    printf("%s\n", str2); // "manx"

    char str3[] = "rhino";
    int tweaks3[] = {1, 1, 1, 1, 1};
    tweakLetters(str3, tweaks3, 5);
    printf("%s\n", str3); // "sijop"

    char str4[] = "hello";
    int tweaks4[] = {0, 0, 0, 0, 0};
    tweakLetters(str4, tweaks4, 5);
    printf("%s\n", str4); // "hello"

    char str5[] = "world";
    int tweaks5[] = {-1, -1, -1, -1, -1};
    tweakLetters(str5, tweaks5, 5);
    printf("%s\n", str5); // "vnmkc"

    return 0;
}