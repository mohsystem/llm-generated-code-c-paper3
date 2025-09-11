
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* generateRandomString(int length) {
    if (length <= 0) {
        return NULL;
    }
    
    const char ALPHA[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int ALPHA_LENGTH = sizeof(ALPHA) - 1;
    
    char* result = (char*)malloc((length + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    FILE* urandom = fopen("/dev/urandom", "r");
    if (urandom == NULL) {
        free(result);
        return NULL;
    }
    
    unsigned char byte;
    for (int i = 0; i < length; i++) {
        if (fread(&byte, 1, 1, urandom) != 1) {
            free(result);
            fclose(urandom);
            return NULL;
        }
        result[i] = ALPHA[byte % ALPHA_LENGTH];
    }
    
    result[length] = '\\0';
    fclose(urandom);
    return result;
}

int main() {
    char* result;
    
    // Test cases
    int test_lengths[] = {5, 10, 15, 20, 1};
    for(int i = 0; i < 5; i++) {
        result = generateRandomString(test_lengths[i]);
        if (result != NULL) {
            printf("%s\\n", result);
            free(result);
        } else {
            printf("Error generating random string\\n");
        }
    }
    
    return 0;
}
