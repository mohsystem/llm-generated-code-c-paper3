
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <regex.h>
#include <sys/stat.h>

#define MAX_FILENAME_LENGTH 256
#define ENCRYPTION_KEY "MySuperSecretKey"

struct WriteData {
    FILE *fp;
    size_t size;
};

static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *stream) {
    struct WriteData *data = (struct WriteData *)stream;
    size_t written = fwrite(ptr, size, nmemb, data->fp);
    data->size += written;
    return written;
}

static char* decrypt_password(const char* encrypted_password) {
    // Simplified decryption - in real implementation use proper encryption
    return strdup(encrypted_password);
}

static int is_valid_filename(const char* filename) {
    regex_t regex;
    int reti;
    
    reti = regcomp(&regex, "^[a-zA-Z0-9._-]+$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\\n");
        return 0;
    }
    
    reti = regexec(&regex, filename, 0, NULL, 0);
    regfree(&regex);
    
    return reti == 0;
}

int download_from_ftp(const char* hostname, const char* username, 
                     const char* password, const char* filename) {
    CURL *curl;
    CURLcode res;
    struct WriteData write_data;
    char url[512];
    char* decrypted_pass = NULL;
    FILE* fp = NULL;
    int success = 0;
    
    // Validate inputs
    if (!hostname || !username || !password || !filename) {
        fprintf(stderr, "Error: Invalid parameters\\n");
        return 0;
    }
    
    if (strlen(filename) > MAX_FILENAME_LENGTH) {
        fprintf(stderr, "Error: Filename too long\\n");
        return 0;
    }
    
    if (!is_valid_filename(filename)) {
        fprintf(stderr, "Error: Invalid filename format\\n");
        return 0;
    }
    
    curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Error: Failed to initialize CURL\\n");
        return 0;
    }
    
    decrypted_pass = decrypt_password(password);
    if (!decrypted_pass) {
        fprintf(stderr, "Error: Password decryption failed\\n");
        goto cleanup;
    }
    
    fp = fopen(filename, "wb");
    if (!fp) {
        fprintf(stderr, "Error: Cannot open file for writing\\n");
        goto cleanup;
    }
    
    write_data.fp = fp;
    write_data.size = 0;
    
    snprintf(url, sizeof(url), "ftp://%s/%s", hostname, filename);
    
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERNAME, username);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, decrypted_pass);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURL', type='text')