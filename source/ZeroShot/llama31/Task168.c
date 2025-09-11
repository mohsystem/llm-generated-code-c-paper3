#include <stdio.h>
#include <string.h>

char* tweakLetters(char* str, int* tweaks, int size) {
    for (int i = 0; i < size; i++) {
        str[i] = str[i] + tweaks[i];
    }
    return str;
}

int main() {
    char str1[] = "apple";
    char str2[] = "many";
    char str3[] = "rhino";
    char str4[] = "hello";
    char str5[] = "world";

    int tweaks1[] = {0, 1, -1, 0, -1};
    int tweaks2[] = {0, 0, 0, -1};
    int tweaks3[] = {1, 1, 1, 1, 1};
    int tweaks4[] = {0, 0, 0, 0, 0};
    int tweaks5[] = {-1, -1, -1, -1, -1};

    printf("%s\n", tweakLetters(str1, tweaks1, 5)); // "aqold"
    printf("%s\n", tweakLetters(str2, tweaks2, 4)); // "manx"
    printf("%s\n", tweakLetters(str3, tweaks3, 5)); // "sijop"
    printf("%s\n", tweakLetters(str4, tweaks4, 5)); // "hello"
    printf("%s\n", tweakLetters(str5, tweaks5, 5)); // "vnqkc"

    return 0;
}