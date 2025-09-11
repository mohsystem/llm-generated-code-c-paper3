#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

const char ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

void generate_random_string(int length, char* result) {
    srand(time(NULL));
    for (int i = 0; i < length; ++i) {
        result[i] = ALPHABET[rand() % (sizeof(ALPHABET) - 1)];
    }
    result[length] = '\0';
}

int main() {
    char result[31];
    generate_random_string(10, result);
    printf("%s\n", result);
    generate_random_string(15, result);
    printf("%s\n", result);
    generate_random_string(20, result);
    printf("%s\n", result);
    generate_random_string(25, result);
    printf("%s\n", result);
    generate_random_string(30, result);
    printf("%s\n", result);
    return 0;
}