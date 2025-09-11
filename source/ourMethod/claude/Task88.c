
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PATH 4096
#define STRING_LENGTH 10

char* createTempFileWithUnicode() {
    static char temp_path[MAX_PATH];
    char random_string[STRING_LENGTH + 1];
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    FILE* temp_file;
    
    // Generate temporary file name
    #ifdef _WIN32
        if(tmpnam_s(temp_path, MAX_PATH) != 0) {
            return NULL;
        }
    #else
        if(tmpnam(temp_path) == NULL) {
            return NULL;
        }
    #endif
    
    // Generate random string
    srand((unsigned int)time(NULL));
    for(int i = 0; i < STRING_LENGTH; i++) {
        random_string[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    random_string[STRING_LENGTH] = '\\0';
    
    // Open file for writing
    #ifdef _WIN32
        if(fopen_s(&temp_file, temp_path, "wb") != 0) {
            return NULL;
        }
    #else
        temp_file = fopen(temp_path, "wb");
        if(temp_file == NULL) {
            return NULL;
        }
    #endif
    
    // Write string to file
    if(fwrite(random_string, sizeof(char), strlen(random_string), temp_file) != strlen(random_string)) {
        fclose(temp_file);
        return NULL;
    }
    
    fclose(temp_file);
    return temp_path;
}

int main() {
    // Test cases
    for(int i = 0; i < 5; i++) {
        char* file_path = createTempFileWithUnicode();
        if(file_path != NULL) {
            printf("Created temp file: %s\\n", file_path);
            
            // Read and display content
            FILE* file;
            #ifdef _WIN32
                if(fopen_s(&file, file_path, "rb") == 0) {
            #else
                file = fopen(file_path, "rb");
                if(file != NULL) {
            #endif
                    char buffer[STRING_LENGTH + 1];
                    size_t bytes_read = fread(buffer, sizeof(char), STRING_LENGTH, file);
                    buffer[bytes_read] = '\\0';
                    printf("File content: %s\\n", buffer);
                    fclose(file);
                }
        } else {
            printf("Error creating temporary file\\n");
        }
    }
    
    return 0;
}
