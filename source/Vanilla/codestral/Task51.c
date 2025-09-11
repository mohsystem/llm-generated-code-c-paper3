#include<stdio.h>
#include<string.h>

void encrypt(char *input, char *output) {
    for (int i = 0; i < strlen(input); i++) {
        output[i] = input[i] + 1;
    }
    output[strlen(input)] = '\0';
}

int main() {
    char output[100];
    encrypt("Hello", output);
    printf("%s\n", output);
    encrypt("World", output);
    printf("%s\n", output);
    encrypt("Java", output);
    printf("%s\n", output);
    encrypt("Python", output);
    printf("%s\n", output);
    encrypt("C++", output);
    printf("%s\n", output);
    return 0;
}