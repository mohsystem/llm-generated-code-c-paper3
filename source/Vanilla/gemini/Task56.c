#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* generate_token() {
    char* token = (char*)malloc(37 * sizeof(char));
    if (token == NULL) {
        return NULL; 
    }

    srand(time(NULL));
    const char charset[] = "0123456789abcdef";

    for (int i = 0; i < 36; i++) {
        if (i == 8 || i == 13 || i == 18 || i == 23) {
            token[i] = '-';
        } else {
            token[i] = charset[rand() % 16];
        }
    }
    token[36] = '\0';
    return token;
}

int main() {
    for (int i = 0; i < 5; i++) {
        char* token = generate_token();
        if (token != NULL) {
            printf("%s\n", token);
            free(token);
        } else {
            fprintf(stderr, "Memory allocation failed!\n");
        }
    }
    return 0;
}