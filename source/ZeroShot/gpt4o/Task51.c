#include <stdio.h>
#include <string.h>

void encrypt(char *input, char *output) {
    for (int i = 0; input[i] != '\0'; i++) {
        output[i] = input[i] + 3; // Simple Caesar Cipher shifting by 3
    }
}

int main() {
    char output[100];
    encrypt("hello", output);
    printf("%s\n", output);  // khoor
    encrypt("world", output);
    printf("%s\n", output);  // zruog
    encrypt("java", output);
    printf("%s\n", output);  // mdyd
    encrypt("test", output);
    printf("%s\n", output);  // whvw
    encrypt("secure", output);
    printf("%s\n", output);  // vhfxuh
    return 0;
}