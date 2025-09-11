#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* generateRandomString(int length) {
    const char LETTERS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int lettersCount = strlen(LETTERS);

    char* result = (char*)malloc(length + 1);
    if (!result) return NULL;

    srand((unsigned int)time(NULL));

    for (int i = 0; i < length; ++i) {
        result[i] = LETTERS[rand() % lettersCount];
    }
    result[length] = '\0';

    return result;
}

int main() {
    char* str1 = generateRandomString(10);
    char* str2 = generateRandomString(15);
    char* str3 = generateRandomString(5);
    char* str4 = generateRandomString(12);
    char* str5 = generateRandomString(20);

    if (str1) printf("%s\n", str1);
    if (str2) printf("%s\n", str2);
    if (str3) printf("%s\n", str3);
    if (str4) printf("%s\n", str4);
    if (str5) printf("%s\n", str5);

    free(str1);
    free(str2);
    free(str3);
    free(str4);
    free(str5);

    return 0;
}