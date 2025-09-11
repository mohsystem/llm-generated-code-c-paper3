
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;
    
    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) {
        printf("Error: not enough memory\\n");
        return 0;
    }
    
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    
    return realsize;
}

struct json_object* fetch_json_from_url(const char* url) {
    if (!url || strlen(url) == 0) {
        fprintf(stderr, "Error: URL cannot be empty\\n");
        return NULL;
    }

    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk;
    struct json_object *json_obj = NULL;

    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
        
        res = curl_easy_perform(curl);
        
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\\n", curl_easy_strerror(res));
        } else {
            json_obj = json_tokener_parse(chunk.memory);
            if (json_obj == NULL) {
                fprintf(stderr, "Error parsing JSON\\n");
            }
        }
        
        curl_easy_cleanup(curl);
    }
    
    free(chunk.memory);
    curl_global_cleanup();
    
    return json_obj;
}

int main() {
    const char* test_urls[] = {
        "https://api.github.com/users/github",
        "https://api.publicapis.org/entries",
        "https://jsonplaceholder.typicode.com/posts/1",
        "https://api.openweathermap.org/data/2.5/weather?q=London&appid=YOUR_API_KEY",
        "https://api.coincap.io/v2/assets/bitcoin"
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Fetching JSON from: %s\\n", test_urls[i]);
        struct json_object *json = fetch_json_from_url(test_urls[i]);
        
        if (json != NULL) {
            printf("Successfully fetched JSON:\\n%s\\n", 
                   json_object_to_json_string_ext(json, JSON_C_TO_STRING_PRETTY));
            json_object_put(json);
        }
        printf("------------------------\\n");
    }
    
    return 0;
}
