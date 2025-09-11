
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct MemoryStruct {
    char* memory;
    size_t size;
};

static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct* mem = (struct MemoryStruct*)userp;

    char* ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(!ptr) {
        printf("Not enough memory\\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

char* fetchJsonFromUrl(const char* url) {
    CURL* curl = curl_easy_init();
    struct MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);

        CURLcode res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\\n", curl_easy_strerror(res));
            free(chunk.memory);
            curl_easy_cleanup(curl);
            return NULL;
        }
        curl_easy_cleanup(curl);
        return chunk.memory;
    }
    free(chunk.memory);
    return NULL;
}

int main() {
    const char* urls[] = {
        "https://jsonplaceholder.typicode.com/todos/1",
        "https://api.github.com/users/github",
        "https://api.publicapis.org/entries",
        "https://api.ipify.org?format=json",
        "https://api.coindesk.com/v1/bpi/currentprice.json"
    };

    curl_global_init(CURL_GLOBAL_ALL);

    for(int i = 0; i < 5; i++) {
        printf("Fetching JSON from: %s\\n", urls[i]);
        char* result = fetchJsonFromUrl(urls[i]);
        if(result) {
            printf("Response: %s\\n", result);
            free(result);
        }
        printf("------------------------\\n");
    }

    curl_global_cleanup();
    return 0;
}
