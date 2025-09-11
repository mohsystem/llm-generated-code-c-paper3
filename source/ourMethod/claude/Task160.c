
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define MAX_BUFFER 102400
#define MAX_URL_LENGTH 2048

struct MemoryStruct {
    char* memory;
    size_t size;
};

static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct* mem = (struct MemoryStruct*)userp;

    if (mem->size + realsize >= MAX_BUFFER) {
        return 0; // Too large, prevent buffer overflow
    }

    char* ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) {
        return 0; // Out of memory
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}

char* make_http_request(const char* url) {
    CURL* curl;
    CURLcode res;
    struct MemoryStruct chunk;
    static char error_buffer[CURL_ERROR_SIZE];
    
    // Initialize chunk
    chunk.memory = malloc(1);
    chunk.size = 0;
    
    if (!chunk.memory) {
        return strdup("Error: Memory allocation failed");
    }

    curl = curl_easy_init();
    if (!curl) {
        free(chunk.memory);
        return strdup("Error: CURL initialization failed");
    }

    // Set options
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, error_buffer);

    res = curl_easy_perform(curl);
    
    if (res != CURLE_OK) {
        free(chunk.memory);
        curl_easy_cleanup(curl);
        return strdup(error_buffer);
    }

    curl_easy_cleanup(curl);
    return chunk.memory;
}

int main() {
    // Initialize CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Test cases
    const char* test_urls[] = {
        "https://www.example.com",
        "https://api.github.com",
        "https://httpbin.org/get",
        "https://postman-echo.com/get",
        "https://jsonplaceholder.typicode.com/posts/1"
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Testing URL: %s\\n", test_urls[i]);
        char* response = make_http_request(test_urls[i]);
        printf("Response: %s\\n", response);
        printf("------------------------\\n");
        free(response);
    }

    // Cleanup
    curl_global_cleanup();
    return 0;
}
