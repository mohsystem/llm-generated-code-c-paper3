#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Note: This C implementation provides a basic random token generation. 
// For stronger security in C, consider using a dedicated cryptography library.

char* generate_random_token(int length) {
    char* token = malloc((length + 1) * sizeof(char));
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
    srand(time(NULL)); // Seed the random number generator

    for (int i = 0; i < length; i++) {
        int index = rand() % (int)(sizeof(charset) - 1);
        token[i] = charset[index];
    }
    token[length] = '\0';
    return token;
}


int main() {
    char* token1 = generate_random_token(16);
    printf("%s\n", token1);
    free(token1);

    char* token2 = generate_random_token(24);
    printf("%s\n", token2);
    free(token2);

    char* token3 = generate_random_token(32);
    printf("%s\n", token3);
    free(token3);

    char* token4 = generate_random_token(8);
    printf("%s\n", token4);
    free(token4);


    char* token5 = generate_random_token(12);
    printf("%s\n", token5);
    free(token5);
    return 0;

}