#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* generateRandomString(int length) {
    if (length < 0) {
         fprintf(stderr,"Length must be non-negative.\n");
        return NULL;
    }

    if (length == 0) {
        char *emptyStr = (char *) malloc(1);
        if (emptyStr == NULL) {
            return NULL; // Handle memory allocation failure
        }
        emptyStr[0] = '\0';
        return emptyStr;
    }

    char *allowedChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int allowedCharsLen = strlen(allowedChars);
    char *randomString = (char *) malloc(length + 1);

    if (randomString == NULL) {
         fprintf(stderr,"Memory allocation failed.\n");
        return NULL; // Handle memory allocation failure
    }


    srand(time(NULL)); // Initialize random seed


    for (int i = 0; i < length; i++) {
        int randomIndex = rand() % allowedCharsLen;
        randomString[i] = allowedChars[randomIndex];
    }
    randomString[length] = '\0'; // Null-terminate

    return randomString;

}

int main() {
    char *str1 = generateRandomString(5);
    if (str1 != NULL) {
      printf("%s\n", str1);
      free(str1);
    }


    char *str2 = generateRandomString(10);
    if (str2 != NULL) {
        printf("%s\n", str2);
        free(str2);
    }


    char *str3 = generateRandomString(0);
    if (str3 != NULL) {
        printf("%s\n", str3);
        free(str3);
    }

    char *str4 = generateRandomString(1);
    if (str4 != NULL) {
        printf("%s\n", str4);
        free(str4);
    }


    char *str5 = generateRandomString(20);
    if (str5 != NULL) {
        printf("%s\n", str5);
        free(str5);
    }



    return 0;
}