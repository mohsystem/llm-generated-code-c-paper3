
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

char* retrieveFile(const char* fileName, const char* serverUrl) {
    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk;
    char url[512];
    
    chunk.memory = malloc(1);
    chunk.size = 0;
    
    sprintf(url, "%s/%s", serverUrl, fileName);
    
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        
        if(res != CURLE_OK) {
            free(chunk.memory);
            return strdup("Error: Failed to retrieve file");
        }
        
        return chunk.memory;
    }
    
    free(chunk.memory);
    return strdup("Error: Could not initialize CURL");
}

int main() {
    const char* serverUrl = "http://example.com/files";
    
    // Test cases
    const char* testFiles[] = {
        "test1.txt",
        "document.pdf",
        "image.jpg",
        "nonexistent.txt",
        "data.csv"
    };
    
    for(int i = 0; i < 5; i++) {
        printf("Retrieving: %s\\n", testFiles[i]);
        char* result = retrieveFile(testFiles[i], serverUrl);
        printf("%s\\n", result);
        printf("------------------------\\n");
        free(result);
    }
    
    return 0;
}
