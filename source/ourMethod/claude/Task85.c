
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LETTERS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

char* generate_random_string(int length) {
    if (length < 0) {
        return NULL;
    }
    
    // Add 1 for null terminator
    char* result = (char*)malloc((length + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // Use high-resolution time for seeding
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    srand((unsigned int)(ts.tv_nsec ^ ts.tv_sec));
    
    int letters_len = strlen(LETTERS);
    for (int i = 0; i < length; i++) {
        result[i] = LETTERS[rand() % letters_len];
    }
    result[length] = '\\0';
    
    return result;
}

int main() {
    // Test cases
    char* str;
    
    str = generate_random_string(5);
    if (str) {
        printf("%s\\n", str);
        free(str);
    }
    
    str = generate_random_string(10);
    if (str) {
        printf("%s\\n", str);
        free(str);
    }
    
    str = generate_random_string(15);
    if (str) {
        printf("%s\\n", str);
        free(str);
    }
    
    str = generate_random_string(20);
    if (str) {
        printf("%s\\n", str);
        free(str);
    }
    
    str = generate_random_string(0);
    if (str) {
        printf("%s\\n", str);
        free(str);
    }
    
    return 0;
}
