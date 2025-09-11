#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// generates a random number of specified length
char* generate_random_number(int length) {
    if (length <= 0) {
        return ""; // Return empty string for non-positive length
    }
    char* str = (char*)malloc(sizeof(char) * (length + 1));
    if (str == NULL) {
        return NULL; // Handle memory allocation failure
    }
    srand((unsigned int)time(NULL)); // Seed the random number generator
    for (int i = 0; i < length; i++) {
        str[i] = (char)((rand() % 10) + '0');
    }
    str[length] = '\0'; // Null-terminate the string
    return str;

}


// generates a random token (UUID version 4)
char* generate_random_token() {

     char* str = (char*)malloc(sizeof(char) * 37);
    if (str == NULL) {
        return NULL; // Handle memory allocation failure
    }

    srand((unsigned int)time(NULL)); // Seed the random number generator

    sprintf(str, "%08x-%04x-4%03x-%04x-%012x",
            rand(), rand() % 65536, rand() % 4096, rand() % 65536, rand());

    return str;
}

int main() {
    char* num1 = generate_random_number(5);
    char * num2 = generate_random_number(10);
    char * num3 = generate_random_number(0);
    char* token1 = generate_random_token();
    char* token2 = generate_random_token();


 if (num1 != NULL) {
        printf("Test case 1: %s\n", num1);
        free(num1); // Free allocated memory
    } else {
        printf("Memory allocation failed for num1\n");
    }

if (num2 != NULL) {
        printf("Test case 2: %s\n", num2);
        free(num2); // Free allocated memory
    } else {
        printf("Memory allocation failed for num2\n");
    }


 if (num3 != NULL) {
        printf("Test case 3: %s\n", num3);
        free(num3); // Free allocated memory
    }


    if (token1 != NULL) {
        printf("Test case 4: %s\n", token1);
        free(token1); // Free allocated memory
    } else {
        printf("Memory allocation failed for token1\n");
    }

 if (token2 != NULL) {
        printf("Test case 5: %s\n", token2);
        free(token2); // Free allocated memory
    } else {
        printf("Memory allocation failed for token2\n");
    }


    return 0;
}