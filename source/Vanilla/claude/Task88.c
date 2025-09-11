
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RANDOM_STRING_LENGTH 10
#define MAX_PATH_LENGTH 1024

char* createTempFileWithUnicode() {
    static char temp_path[MAX_PATH_LENGTH];
    char random_string[RANDOM_STRING_LENGTH + 1];
    char unicode_buffer[RANDOM_STRING_LENGTH * 6 + 1]; // Each char can take up to 6 bytes in Unicode
    int i;
    FILE* fp;
    
    // Create temporary file name
    strcpy(temp_path, "unicode_XXXXXX");
    int fd = mkstemp(temp_path);
    if (fd == -1) {
        return NULL;
    }
    close(fd);
    
    // Generate random string
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for (i = 0; i < RANDOM_STRING_LENGTH; i++) {
        random_string[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    random_string[RANDOM_STRING_LENGTH] = '\\0';
    
    // Convert to Unicode string
    unicode_buffer[0] = '\\0';
    for (i = 0; i < RANDOM_STRING_LENGTH; i++) {
        char temp[7];
        sprintf(temp, "\\\\u%04x", (unsigned int)random_string[i]);
        strcat(unicode_buffer, temp);
    }
    
    // Write to file
    fp = fopen(temp_path, "w");
    if (fp == NULL) {
        return NULL;
    }
    
    fprintf(fp, "%s", unicode_buffer);
    fclose(fp);
    
    return temp_path;
}

int main() {
    // Initialize random seed
    srand(time(NULL));
    
    // Test cases
    for (int i = 0; i < 5; i++) {
        char* file_path = createTempFileWithUnicode();
        if (file_path != NULL) {
            printf("Test case %d: Temp file created at: %s\\n", i+1, file_path);
        } else {
            printf("Test case %d: Failed to create temp file\\n", i+1);
        }
    }
    
    return 0;
}
