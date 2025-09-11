#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char* generateRandomString(int length) {
    static const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char* random_string = (char*) malloc((length + 1) * sizeof(char));
    if (!random_string) {
        return NULL;
    }
    srand(time(NULL));
    for (int i = 0; i < length; ++i) {
        random_string[i] = alphabet[rand() % (sizeof(alphabet) - 1)];
    }
    random_string[length] = '\0';
    return random_string;
}

int main() {
    for (int i = 0; i < 5; ++i) {
        int length = 10 + i * 2; // Test with different lengths
        char* random_string = generateRandomString(length);
        if (random_string) {
            printf("Random String of length %d: %s\n", length, random_string);
            free(random_string);
        }
    }
    return 0;
}