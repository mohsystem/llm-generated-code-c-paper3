
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PATH 1024
#define STR_LENGTH 10

char* createTempFileWithUnicode() {
    static char filepath[MAX_PATH];
    char randomStr[STR_LENGTH + 1];
    char unicodeStr[STR_LENGTH * 6 + 1]; // Each char can take up to 6 bytes in unicode
    FILE* fp;
    int i;
    
    // Generate random string
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for(i = 0; i < STR_LENGTH; i++) {
        randomStr[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    randomStr[STR_LENGTH] = '\\0';
    
    // Convert to unicode string
    unicodeStr[0] = '\\0';
    for(i = 0; i < STR_LENGTH; i++) {
        char temp[7];
        sprintf(temp, "\\\\u%04x", (unsigned int)randomStr[i]);
        strcat(unicodeStr, temp);
    }
    
    // Create temp file
    #ifdef _WIN32
        tmpnam_s(filepath, MAX_PATH);
        strcat(filepath, ".txt");
    #else
        strcpy(filepath, "/tmp/tempXXXXXX");
        mkstemp(filepath);
        strcat(filepath, ".txt");
    #endif
    
    // Write to file
    fp = fopen(filepath, "wb");
    if(fp == NULL) {
        return "Error: Could not create file";
    }
    
    fprintf(fp, "%s", unicodeStr);
    fclose(fp);
    
    return filepath;
}

int main() {
    // Initialize random seed
    srand(time(NULL));
    
    // Test cases
    for(int i = 0; i < 5; i++) {
        printf("Test case %d: %s\\n", i+1, createTempFileWithUnicode());
    }
    
    return 0;
}
