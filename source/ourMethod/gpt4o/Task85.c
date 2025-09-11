#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* generateRandomString(int length) {
    if (length <= 0) return "";
    static const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char* randomString = (char*) malloc((length + 1) * sizeof(char));
    
    if (!randomString) return ""; // Check if memory allocation failed

    srand((unsigned int) time(NULL));
    for (int i = 0; i < length; ++i) {
        randomString[i] = alphabet[rand() % (sizeof(alphabet) - 1)];
    }
    randomString[length] = '\0'; // Null-terminate the string
    return randomString;
}

int main() {
    char* str1 = generateRandomString(5);
    printf("%s\n", str1);
    free(str1);
    
    char* str2 = generateRandomString(10);
    printf("%s\n", str2);
    free(str2);

    char* str3 = generateRandomString(15);
    printf("%s\n", str3);
    free(str3);

    char* str4 = generateRandomString(20);
    printf("%s\n", str4);
    free(str4);

    char* str5 = generateRandomString(25);
    printf("%s\n", str5);
    free(str5);

    return 0;
}