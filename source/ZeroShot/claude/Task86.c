
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <time.h>
#include <stdbool.h>

#define MAX_URL_LENGTH 2048
#define MAX_FILE_SIZE 104857600 // 100MB in bytes

struct WriteData {
    FILE *fp;
    size_t size;
};

static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *stream) {
    struct WriteData *data = (struct WriteData *)stream;
    size_t written = fwrite(ptr, size, nmemb, data->fp);
    data->size += written * size;
    
    if (data->size > MAX_FILE_SIZE) {
        return 0; // Abort transfer if file too large
    }
    return written;
}

bool is_valid_url(const char *url) {
    if (!url) return false;
    
    size_t len = strlen(url);
    if (len < 12) return false; // https://x.exe minimum length
    
    if (strncmp(url, "https://", 8) != 0) return false;
    
    const char *ext = url + len - 4;
    if (strcasecmp(ext, ".exe") != 0) return false;
    
    return true;
}

char* generate_temp_filename() {
    char *filename = malloc(32);
    if (!filename) return NULL;
    
    srand(time(NULL));
    snprintf(filename, 32, "download_%x%x.exe", rand(), rand());
    return filename;
}

bool download_and_execute(const char *url) {
    if (!is_valid_url(url)) {
        return false;
    }
    
    CURL *curl = curl_easy_init();
    if (!curl) {
        return false;
    }
    
    char *temp_filename = generate_temp_filename();
    if (!temp_filename) {
        curl_easy_cleanup(curl);
        return false;
    }
    
    FILE *fp = fopen(temp_filename, "wb");
    if (!fp) {
        free(temp_filename);
        curl_easy_cleanup(curl);
        return false;
    }
    
    struct WriteData write_data = {fp, 0};
    
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &write_data);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
    
    CURLcode res = curl_easy_perform(curl);
    fclose(fp);
    
    bool success = false;
    if (res == CURLE_OK) {
        // Execute file
        #ifdef _WIN32
        success = (system(temp_filename) != -1);
        #else
        char command[1024];
        snprintf(command, sizeof(command), "chmod +x %s && %s", temp_filename, temp_filename);
        success = (system(command) != -1);
        #endif
    }
    
    // Cleanup
    remove(temp_filename);
    free(temp_filename);
    curl_easy_cleanup(curl);
    
    return success;
}

int main() {
    // Test cases
    const char *test_urls[] = {
        "https://example.com/valid.exe",
        "http://unsecure.com/file.exe",
        "https://example.com/notexe.txt",
        "invalid_url",
        "https://example.com/toolarge.exe"
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Testing URL: %s\\n", test_urls[i]);
        bool result = download_and_execute(test_urls[i]);
        printf("Result: %s\\n", result ? "true" : "false");
    }
    
    return 0;
}
