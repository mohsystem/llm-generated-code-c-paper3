
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <curl/curl.h>

#define MAX_FILE_SIZE 104857600 // 100MB
#define MAX_PATH 4096

struct MemoryStruct {
    char* memory;
    size_t size;
};

static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct* mem = (struct MemoryStruct*)userp;

    if (mem->size + realsize > MAX_FILE_SIZE) {
        return 0; // Abort if file too large
    }

    char* ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) {
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

int download_and_execute(const char* url) {
    if (!url || strlen(url) < 5) {
        printf("Security Error: Invalid URL\\n");
        return 0;
    }

    // Check file extension
    const char* ext = url + strlen(url) - 4;
    if (strcasecmp(ext, ".exe") != 0) {
        printf("Security Error: Only .exe files are allowed\\n");
        return 0;
    }

    CURL* curl = curl_easy_init();
    if (!curl) {
        printf("Error: CURL initialization failed\\n");
        return 0;
    }

    struct MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    // Set up CURL options
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        printf("Error: %s\\n", curl_easy_strerror(res));
        free(chunk.memory);
        curl_easy_cleanup(curl);
        return 0;
    }

    // Create temporary filename
    char tempfile[MAX_PATH];
    #ifdef _WIN32
        char temppath[MAX_PATH];
        GetTempPath(MAX_PATH, temppath);
        snprintf(tempfile, MAX_PATH, "%sdownload_%ld.exe", temppath, time(NULL));
    #else
        snprintf(tempfile, MAX_PATH, "/tmp/download_%ld.exe", time(NULL));
    #endif

    // Save file
    FILE* fp = fopen(tempfile, "wb");
    if (!fp) {
        printf("Error: Cannot create temporary file\\n");
        free(chunk.memory);
        curl_easy_cleanup(curl);
        return 0;
    }

    fwrite(chunk.memory, 1, chunk.size, fp);
    fclose(fp);

    // Execute file
    printf("Security Warning: Executing downloaded file. Proceed with caution.\\n");
    #ifdef _WIN32
        system(tempfile);
    #else
        char cmd[MAX_PATH + 10];
        snprintf(cmd, sizeof(cmd), "chmod +x %s && %s", tempfile, tempfile);
        system(cmd);
    #endif

    // Cleanup
    remove(tempfile);
    free(chunk.memory);
    curl_easy_cleanup(curl);
    return 1;
}

int main() {
    const char* test_urls[] = {
        "https://example.com/safe1.exe",
        "https://example.com/safe2.exe",
        "https://example.com/safe3.exe",
        "https://example.com/safe4.exe",
        "https://example.com/safe5.exe"
    };

    for (int i = 0; i < 5; i++) {
        printf("Testing URL: %s\\n", test_urls[i]);
        download_and_execute(test_urls[i]);
        printf("-------------------\\n");
    }

    return 0;
}
