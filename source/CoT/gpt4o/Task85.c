#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateRandomString(int length, char* output) {
    const char* ASCII_LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    size_t letters_count = 52;

    for (int i = 0; i < length; ++i) {
        output[i] = ASCII_LETTERS[rand() % letters_count];
    }
    output[length] = '\0';
}

int main() {
    srand((unsigned int)time(NULL));

    char output1[11];
    generateRandomString(10, output1);
    printf("%s\n", output1);

    char output2[16];
    generateRandomString(15, output2);
    printf("%s\n", output2);

    char output3[21];
    generateRandomString(20, output3);
    printf("%s\n", output3);

    char output4[6];
    generateRandomString(5, output4);
    printf("%s\n", output4);

    char output5[26];
    generateRandomString(25, output5);
    printf("%s\n", output5);

    return 0;
}