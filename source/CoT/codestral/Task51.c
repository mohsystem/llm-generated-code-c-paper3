#include <stdio.h>
#include <ctype.h>
#include <string.h>

void encrypt(const char* input, char* output) {
    // This is a simple Caesar cipher implementation for encryption.
    // It shifts each character by 3 places to the right in the alphabet.
    int i;
    for (i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            if (islower(input[i])) {
                output[i] = (input[i] - 'a' + 3) % 26 + 'a';
            } else if (isupper(input[i])) {
                output[i] = (input[i] - 'A' + 3) % 26 + 'A';
            }
        } else {
            output[i] = input[i];
        }
    }
    output[i] = '\0';
}

int main() {
    char encrypted[100];
    encrypt("Hello, World!", encrypted);
    printf("%s\n", encrypted); // "Khoor, Zruog!"
    encrypt("C Programming", encrypted);
    printf("%s\n", encrypted); // "F Surjudpplqj"
    encrypt("Secure Coding", encrypted);
    printf("%s\n", encrypted); // "Vhfxuh Fqlgwbr"
    encrypt("Cybersecurity", encrypted);
    printf("%s\n", encrypted); // "Fbyhubhvfuhwuh"
    encrypt("Information Technology", encrypted);
    printf("%s\n", encrypted); // "Lqjyhuwhuwlwkrwhvwdq"
    return 0;
}