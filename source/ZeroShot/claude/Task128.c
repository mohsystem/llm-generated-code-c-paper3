
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generateRandomToken(char *token, int length) {
    const char charset[] = "0123456789"
                          "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                          "abcdefghijklmnopqrstuvwxyz";
    int charset_length = strlen(charset);
    
    FILE *urandom = fopen("/dev/urandom", "r");
    if (urandom) {
        unsigned char byte;
        for (int i = 0; i < length; i++) {
            fread(&byte, 1, 1, urandom);
            token[i] = charset[byte % charset_length];
        }
        fclose(urandom);
    } else {
        // Fallback to less secure method if /dev/urandom is not available
        srand(time(NULL));
        for (int i = 0; i < length; i++) {
            token[i] = charset[rand() % charset_length];
        }
    }
    token[length] = '\\0';
}

int generateRandomNumber(int min, int max) {
    FILE *urandom = fopen("/dev/urandom", "r");
    unsigned int num;
    
    if (urandom) {
        fread(&num, sizeof(num), 1, urandom);
        fclose(urandom);
    } else {
        // Fallback to less secure method
        srand(time(NULL));
        num = rand();
    }
    
    return min + (num % (max - min + 1));
}

int main() {
    char token[17]; // 16 chars + null terminator
    
    printf("Random Tokens:\\n");
    for(int i = 0; i < 5; i++) {
        generateRandomToken(token, 16);
        printf("%s\\n", token);
    }
    
    printf("\\nRandom Numbers (1-100):\\n");
    for(int i = 0; i < 5; i++) {
        printf("%d\\n", generateRandomNumber(1, 100));
    }
    
    return 0;
}
