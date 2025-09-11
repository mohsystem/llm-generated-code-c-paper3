#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateSecureToken(int length, char *buffer) {
    const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    size_t characters_len = sizeof(characters) - 1;

    srand(time(NULL));

    for (int i = 0; i < length; i++) {
        buffer[i] = characters[rand() % characters_len];
    }
    buffer[length] = '\0';
}

int main() {
    char token[31];
    
    generateSecureToken(10, token); // Test case 1
    printf("%s\n", token);

    generateSecureToken(15, token); // Test case 2
    printf("%s\n", token);

    generateSecureToken(20, token); // Test case 3
    printf("%s\n", token);

    generateSecureToken(25, token); // Test case 4
    printf("%s\n", token);

    generateSecureToken(30, token); // Test case 5
    printf("%s\n", token);

    return 0;
}