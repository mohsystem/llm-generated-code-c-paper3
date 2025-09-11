#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_random_token(int length, char* token) {
    const char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    size_t chars_len = sizeof(chars) - 1;

    for (int i = 0; i < length; i++) {
        token[i] = chars[rand() % chars_len];
    }
    token[length] = '\0';
}

void run_tests() {
    char token[31];
    generate_random_token(10, token);
    printf("%s\n", token);
    generate_random_token(15, token);
    printf("%s\n", token);
    generate_random_token(20, token);
    printf("%s\n", token);
    generate_random_token(25, token);
    printf("%s\n", token);
    generate_random_token(30, token);
    printf("%s\n", token);
}

int main() {
    srand(time(NULL));
    run_tests();
    return 0;
}