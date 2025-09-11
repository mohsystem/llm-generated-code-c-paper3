
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PATH 1024
#define RANDOM_STR_LEN 10

char* createTempFileWithUnicode() {
    static char filepath[MAX_PATH];
    char random_str[RANDOM_STR_LEN + 1];
    FILE* fp;
    int i;
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    
    // Generate random string
    srand(time(NULL));
    for(i = 0; i < RANDOM_STR_LEN; i++) {
        random_str[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    random_str[RANDOM_STR_LEN] = '\\0';
    
    // Create temporary file
    #ifdef _WIN32
        char temp_path[MAX_PATH];
        GetTempPath(MAX_PATH, temp_path);
        snprintf(filepath, MAX_PATH, "%sunicode_%s.txt", temp_path, random_str);
    #else
        snprintf(filepath, MAX_PATH, "/tmp/unicode_%s.txt", random_str);
    #endif
    
    // Open file and write with UTF-8 BOM
    fp = fopen(filepath, "wb");
    if (!fp) {
        return "Error: Could not create file";
    }
    
    // Write UTF-8 BOM
    unsigned char bom[] = {0xEF, 0xBB, 0xBF};
    fwrite(bom, sizeof(unsigned char), 3, fp);
    
    // Write random string
    fwrite(random_str, sizeof(char), strlen(random_str), fp);
    fclose(fp);
    
    return filepath;
}

int main() {
    // Test cases
    for(int i = 0; i < 5; i++) {
        printf("Test case %d: %s\\n", i+1, createTempFileWithUnicode());
        // Add delay to ensure different random strings
        #ifdef _WIN32
            Sleep(1000);
        #else
            sleep(1);
        #endif
    }
    return 0;
}
