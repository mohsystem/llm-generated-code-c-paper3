
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define MAX_BUFFER 102400
#define MAX_TITLE 1024

struct MemoryStruct {
    char* memory;
    size_t size;
};

static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct* mem = (struct MemoryStruct*)userp;

    if(mem->size + realsize >= MAX_BUFFER) {
        return 0; // Too large, prevent buffer overflow
    }

    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if(mem->memory == NULL) {
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

char* extract_title(const char* html) {
    static char title[MAX_TITLE];
    const char* title_start = strstr(html, "<title>");
    const char* title_end;
    
    title[0] = '\0';
    
    if(title_start) {
        title_start += 7; // Skip "<title>"
        title_end = strstr(title_start, "</title>");
        
        if(title_end) {
            size_t length = title_end - title_start;
            if(length < MAX_TITLE) {
                strncpy(title, title_start, length);
                title[length] = '\0';
            }
        }
    }
    
    return title;
}

char* get_page_title(const char* url) {
    CURL* curl;
    CURLcode res;
    static char error_buffer[CURL_ERROR_SIZE];
    struct MemoryStruct chunk;
    static char result[MAX_TITLE];

    chunk.memory = malloc(1);
    chunk.size = 0;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, error_buffer);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            snprintf(result, MAX_TITLE, "Error: %s", error_buffer);
        } else {
            strncpy(result, extract_title(chunk.memory), MAX_TITLE - 1);
            result[MAX_TITLE - 1] = '\0';
        }

        curl_easy_cleanup(curl);
        free(chunk.memory);
    }

    return result;
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Please provide URL as argument\\n");
        return 1;
    }

    // Initialize CURL globally
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Test cases
    const char* urls[] = {
        "https://www.example.com",
        "https://www.google.com",
        "https://www.github.com",
        "https://www.wikipedia.org",
        argv[1]
    };

    for(int i = 0; i < 5; i++) {
        printf("URL: %s\\n", urls[i]);
        printf("Title: %s\\n\\n", get_page_title(urls[i]));
    }

    // Cleanup CURL
    curl_global_cleanup();

    return 0;
}
