#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateToken(int length, char* token) {
    const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    srand(time(NULL));
    for (int i = 0; i < length; ++i) {
        int index = rand() % (sizeof(characters) - 1);
        token[i] = characters[index];
    }
    token[length] = '\0';
}

int main() {
    char token[31];
    generateToken(10, token);
    printf("%s\n", token); // Test case 1
    generateToken(15, token);
    printf("%s\n", token); // Test case 2
    generateToken(20, token);
    printf("%s\n", token); // Test case 3
    generateToken(25, token);
    printf("%s\n", token); // Test case 4
    generateToken(30, token);
    printf("%s\n", token); // Test case 5

    return 0;
}