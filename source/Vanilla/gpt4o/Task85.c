#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateRandomString(char *str, int length) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < length; i++) {
        int key = rand() % (int)(sizeof(charset) - 1);
        str[i] = charset[key];
    }
    str[length] = '\0';
}

int main() {
    srand(time(0));
    char str[26];
    generateRandomString(str, 5);
    printf("%s\n", str);
    generateRandomString(str, 10);
    printf("%s\n", str);
    generateRandomString(str, 15);
    printf("%s\n", str);
    generateRandomString(str, 20);
    printf("%s\n", str);
    generateRandomString(str, 25);
    printf("%s\n", str);
    return 0;
}