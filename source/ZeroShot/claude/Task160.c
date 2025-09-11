
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;
    
    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(!ptr) {
        printf("Error: Not enough memory\\n");
        return 0;
    }
    
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}

char* makeHttpRequest(const char* url) {
    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk;
    
    chunk.memory = malloc(1);
    chunk.size = 0;
    
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");
        
        res = curl_easy_perform(curl);
        
        if(res != CURLE_OK) {
            sprintf(chunk.memory, "Error: %s", curl_easy_strerror(res));
        }
        
        curl_easy_cleanup(curl);
    }
    
    return chunk.memory;
}

int main() {
    const char* urls[] = {
        "https://www.google.com",
        "https://api.github.com",
        "https://httpbin.org/get",
        "http://example.com",
        "https://invalid.domain.123"
    };
    
    curl_global_init(CURL_GLOBAL_ALL);
    
    for(int i = 0; i < 5; i++) {
        printf("Testing URL: %s\\n", urls[i]);
        char* response = makeHttpRequest(urls[i]);
        printf("%s\\n", response);
        printf("------------------------\\n");
        free(response);
    }
    
    curl_global_cleanup();
    return 0;
}
