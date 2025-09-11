#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

char* random_string(int length) {
    const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char* result = malloc(length + 1);

    if (result) {
        srand(time(0));
        for (int i = 0; i < length; i++) {
            result[i] = alphabet[rand() % (sizeof(alphabet) - 1)];
        }
        result[length] = '\0';
    }

    return result;
}

int main() {
    printf("%s\n", random_string(10));
    printf("%s\n", random_string(20));
    printf("%s\n", random_string(30));
    printf("%s\n", random_string(40));
    printf("%s\n", random_string(50));

    return 0;
}