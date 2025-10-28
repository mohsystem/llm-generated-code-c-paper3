
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <errno.h>

#define MAX_FILE_SIZE (10 * 1024 * 1024) // 10MB limit
#define MAX_FILENAME_LEN 256
#define MAX_BUFFER_SIZE 1024

int is_safe_filename(const char* filename) {
    if (filename == NULL || strlen(filename) == 0) {
        return 0;
    }
    
    for (size_t i = 0; i < strlen(filename); i++) {
        char c = filename[i];
        if (!isalnum(c) && c != '.' && c != '-' && c != '_') {
            return 0;
        }
    }
    return 1;
}

char* sanitize_filename(const char* filename) {
    if (filename == NULL) {
        return NULL;
    }
    
    const char* lastSlash = strrchr(filename, '/');
    const char* lastBackslash = strrchr(filename, '\\\\');    const char* basename = filename;        if (lastSlash != NULL) {        basename = lastSlash + 1;    }
    if (lastBackslash != NULL && lastBackslash > basename) {        basename = lastBackslash + 1;    }
    char* sanitized = (char*)malloc(strlen(basename) + 1);    if (sanitized != NULL) {        strcpy(sanitized, basename);    }
    return sanitized;}char* read_file_securely(const char* filename) {    if (filename == NULL || strlen(filename) == 0) {
        char* error = (char*)malloc(100);        strcpy(error, "Error: Filename cannot be null or empty");        return error;
    }        char* sanitized = sanitize_filename(filename);    if (sanitized == NULL) {        char* error = (char*)malloc(100);
        strcpy(error, "Error: Memory allocation failed");        return error;    }        if (!is_safe_filename(sanitized)) {
            char* error = (char*)malloc(150);        strcpy(error, "Error: Invalid filename format. Only alphanumeric, dots, hyphens, and underscores allowed");
            free(sanitized);        return error;
        }        struct stat st;    if (stat(sanitized, &st) != 0) {        char* error = (char*)malloc(100);
            if (errno == ENOENT) {            strcpy(error, "Error: File does not exist");        } else {
                sprintf(error, "Error: Unable to access file - %s", strerror(errno));
            }        free(sanitized);        return error;    }        if (!S_ISREG(st.st_mode)) {        char* error = (char*)malloc(100);
                strcpy(error, "Error: Not a regular file");        free(sanitized);        return error;    }        if (st.st_size > MAX_FILE_SIZE) {
                    char* error = (char*)malloc(100);        strcpy(error, "Error: File size exceeds maximum allowed size");        free(sanitized);
                    return error;
                }        FILE* file = fopen(sanitized, "rb");    if (file == NULL) {        char* error = (char*)malloc(150);
                    sprintf(error, "Error: Unable to open file - %s", strerror(errno));        free(sanitized);        return error;    }
    char* content = (char*)malloc(st.st_size + 1);    if (content == NULL) {        char* error = (char*)malloc(100);
        strcpy(error, "Error: Memory allocation failed");        fclose(file);        free(sanitized);        return error;    }
    size_t bytesRead = fread(content, 1, st.st_size, file);    content[bytesRead] = '\0';
    
    fclose(file);
    free(sanitized);
    
    return content;
}

int main() {
    char* result;
    
    printf("Test 1 - Valid file:\\");
    result = read_file_securely("test.txt");
    printf("%s\\", result);
    free(result);
    
    printf("Test 2 - NULL filename:\\");
    result = read_file_securely(NULL);
    printf("%s\\", result);
    free(result);
    
    printf("Test 3 - Empty filename:\\");
    result = read_file_securely("");
    printf("%s\\", result);
    free(result);
    
    printf("Test 4 - Path traversal attempt:\\");
    result = read_file_securely("../etc/passwd");
    printf("%s\\", result);
    free(result);
    
    printf("Test 5 - Non-existent file:\\");
    result = read_file_securely("nonexistent.txt");
    printf("%s\\", result);
    free(result);
    
    return 0;
}
