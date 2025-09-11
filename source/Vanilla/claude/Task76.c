
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
        printf("Error: not enough memory\\n");
        return 0;
    }
    
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    
    return realsize;
}

char* extractTitle(const char* url) {
    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk;
    static char title[1024];
    
    chunk.memory = malloc(1);
    chunk.size = 0;
    
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        
        res = curl_easy_perform(curl);
        
        if(res == CURLE_OK) {
            char *titleStart = strstr(chunk.memory, "<title>");
            if(titleStart) {
                char *titleEnd = strstr(titleStart, "</title>");
                if(titleEnd) {
                    titleStart += 7;
                    int length = titleEnd - titleStart;
                    if(length > 1023) length = 1023;
                    strncpy(title, titleStart, length);
                    title[length] = '\\0';
                } else {
                    strcpy(title, "Title not found");
                }
            } else {
                strcpy(title, "Title not found");
            }
        } else {
            sprintf(title, "Error: %s", curl_easy_strerror(res));
        }
        
        curl_easy_cleanup(curl);
    }
    
    free(chunk.memory);
    return title;
}

int main() {
    const char* testUrls[] = {
        "https://www.google.com",
        "https://www.github.com",
        "https://www.wikipedia.org",
        "https://www.microsoft.com",
        "https://www.amazon.com"
    };
    
    int numUrls = sizeof(testUrls) / sizeof(testUrls[0]);
    
    for(int i = 0; i < numUrls; i++) {
        printf("URL: %s\\n", testUrls[i]);
        printf("Title: %s\\n\\n", extractTitle(testUrls[i]));
    }
    
    return 0;
}
