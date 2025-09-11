#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* generateRandomString(int length) {
    if (length <= 0) {
        return "";
    }

    char *str = malloc((length + 1) * sizeof(char)); // Allocate memory for the string
    if (str == NULL) {
        return NULL; // Handle memory allocation failure
    }
    
    srand(time(NULL)); // Seed the random number generator

    for (int i = 0; i < length; i++) {
        int randomInt = rand() % 52; // Generate random int 0-51
        char randomChar = (randomInt < 26) ? ('A' + randomInt) : ('a' + (randomInt - 26));
        str[i] = randomChar;
    }
    str[length] = '\0'; // Null-terminate the string

    return str;
}

int main() {
    char *str1 = generateRandomString(5);
    printf("%s\n", str1);
    free(str1);

    char *str2 = generateRandomString(10);
    printf("%s\n", str2);
    free(str2);

    char *str3 = generateRandomString(0);
    printf("%s\n", str3);
    //No need to free str3 as it points to a string literal

    char *str4 = generateRandomString(1);
    printf("%s\n", str4);
    free(str4);


    char *str5 = generateRandomString(20);
    printf("%s\n", str5);
    free(str5);

    return 0;
}