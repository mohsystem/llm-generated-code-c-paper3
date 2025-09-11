
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <regex.h>
#include <unistd.h>
#include <errno.h>

#define TIMEOUT 5L
#define MAX_RETRY 3
#define MAX_PATH 4096
#define BUFFER_SIZE 8192

struct WriteData {
    FILE *fp;
    size_t bytes_written;
};

static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *stream) {
    struct WriteData *wd = (struct WriteData*)stream;
    size_t bytes = fwrite(ptr, size, nmemb, wd->fp);
    wd->bytes_written += bytes;
    return bytes;
}

int validate_input(const char* str, const char* pattern) {
    if (!str || !pattern) return 0;
    
    regex_t regex;
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) return 0;
    
    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    
    return (ret == 0);
}

void secure_clear(void* ptr, size_t size) {
    volatile unsigned char *p = ptr;
    while (size--) *p++ = 0;
}

int download_file(const char* hostname, const char* username, 
                 const char* password, const char* filename) {
    if (!hostname || !username || !password || !filename) {
        fprintf(stderr, "Invalid parameters\\n");
        return 0;
    }
    
    // Validate inputs
    if (!validate_input(hostname, "^[a-zA-Z0-9.-]+$") ||
        !validate_input(username, "^[a-zA-Z0-9._-]+$") ||
        !validate_input(filename, "^[a-zA-Z0-9._-]+$")) {
        fprintf(stderr, "Invalid input format\\n");
        return 0;
    }
    
    CURL *curl = NULL;
    FILE *fp = NULL;
    char temp_path[MAX_PATH];
    char url[MAX_PATH];
    int success = 0;
    struct WriteData wd = {NULL, 0};
    
    curl_global_init(CURL_GLOBAL_DEFAULT);
    
    do {
        // Create temporary file
        snprintf(temp_path, sizeof(', type='text')