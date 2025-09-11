
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define MAX_FILENAME_LENGTH 256
#define MAX_URL_LENGTH 1024
#define MAX_RESPONSE_SIZE 1048576  // 1MB

struct MemoryStruct {
    char* memory;
    size_t size;
};

static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct* mem = (struct MemoryStruct*)userp;

    if (mem->size + realsize > MAX_RESPONSE_SIZE) {
        return 0;  // Too large, abort
    }

    char* ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) {
        return 0;  // Out of memory
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}

int is_valid_filename(const char* filename) {
    if (!filename || strlen(filename) == 0) return 0;
    if (strstr(filename, "..") != NULL) return 0;
    if (strchr(filename, '/') != NULL) return 0;
    if (strchr(filename, '\\\\') != NULL) return 0;
    return 1;
}

char* retrieve_file(const char* filename, const char* server_url) {
    if (!is_valid_filename(filename) || !server_url) {
        return strdup("Invalid input parameters");
    }

    CURL* curl = curl_easy_init();
    if (!curl) {
        return strdup("Failed to initialize CURL");
    }

    struct MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    char url[MAX_URL_LENGTH];
    snprintf(url, sizeof(url), "%s/%s", server_url, filename);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        free(chunk.memory);
        return strdup(curl_easy_strerror(res));
    }

    return chunk.memory;
}

int main() {
    const char* server_url = "https://example.com/files";

    // Test cases
    char* result;

    printf("Test 1: ");
    result = retrieve_file("test.txt", server_url);
    printf("%s\\n", result);
    free(result);

    printf("Test 2: ");
    result = retrieve_file("../secret.txt", server_url);
    printf("%s\\n", result);
    free(result);

    printf("Test 3: ");
    result = retrieve_file("", server_url);
    printf("%s\\n", result);
    free(result);

    printf("Test 4: ");
    result = retrieve_file("document.pdf", server_url);
    printf("%s\\n", result);
    free(result);

    printf("Test 5: ");
    result = retrieve_file("image.jpg", server_url);
    printf("%s\\n", result);
    free(result);

    return 0;
}
