#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* generateRandomNumber(int length) {
    char* randomNumber = (char*)malloc(sizeof(char) * (length + 1));
    if (randomNumber == NULL) {
        return NULL; // Handle memory allocation failure
    }

    srand(time(NULL)); // Seed the random number generator

    for (int i = 0; i < length; i++) {
        randomNumber[i] = (rand() % 10) + '0';
    }
    randomNumber[length] = '\0';
    return randomNumber;
}


char* generateRandomToken(int length) {
    char* token = (char*)malloc(sizeof(char) * (length + 1));
     if (token == NULL) {
        return NULL;
    }

    const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
    srand(time(NULL)); 

    for (int i = 0; i < length; i++) {
        token[i] = characters[rand() % (sizeof(characters) - 1)];
    }
    token[length] = '\0';
    return token;
}


int main() {
    char* num1 = generateRandomNumber(10);
    char* token1 = generateRandomToken(16);
    char* num2 = generateRandomNumber(5);
    char* token2 = generateRandomToken(24);
    char* num3 = generateRandomNumber(12);

     if (num1 != NULL && token1 != NULL && num2 != NULL && token2 != NULL && num3 != NULL) {
        printf("Test case 1: %s\n", num1);
        printf("Test case 2: %s\n", token1);
        printf("Test case 3: %s\n", num2);
        printf("Test case 4: %s\n", token2);
        printf("Test case 5: %s\n", num3);


        free(num1);
        free(token1);
        free(num2);
        free(token2);
        free(num3);

    } else {
      fprintf(stderr, "Memory allocation failed.\n");
      return 1; 
    }
    


    return 0;
}