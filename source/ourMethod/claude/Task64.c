
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1048576  // 1MB
#define URL_MAX_LENGTH 2048
#define TIMEOUT_SECONDS 5

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    // Check for buffer overflow
    if (mem->size + realsize > MAX_BUFFER_SIZE) {
        return 0;  // Signal error to curl
    }

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) {
        return 0;  // Signal error to curl
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

struct json_object* fetchJsonFromUrl(const char* url) {
    // Input validation
    if (!url || strlen(url) == 0 || strlen(url) >= URL_MAX_LENGTH) {
        fprintf(stderr, "Invalid URL\\n");
        return NULL;
    }

    // Validate URL protocol
    if (strncmp(url, "http://", 7) != 0 && strncmp(url, "https://", 8) != 0) {
        fprintf(stderr, "Only HTTP/HTTPS protocols are supported\\n");
        return NULL;
    }

    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk;
    struct json_object *json = NULL;

    // Initialize memory chunk
    chunk.memory = malloc(1);
    if (!chunk.memory) {
        fprintf(stderr, "Failed to allocate memory\\n");
        return NULL;
    }
    chunk.size = 0;

    curl = curl_easy_init();
    if (!curl) {
        free(chunk.memory);
        fprintf(stderr, "Failed to initialize CURL\\n");
        return NULL;
    }

    // Set CURL options
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, TIMEOUT_SECONDS);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");

    // Perform request
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "CURL error: %s\\n", curl_easy_strerror(res));
        goto cleanup;
    }

    // Check HTTP response code
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    if (http_code != 200) {
        fprintf(stderr, "HTTP error: %ld\\n", http_code);
        goto cleanup;
    }

    // Parse JSON
    json = json_tokener_parse(chunk.memory);
    if (!json) {
        fprintf(stderr, "Failed to parse JSON\\n");
    }

cleanup:
    curl_easy_cleanup(curl);
    free(chunk.memory);
    return json;
}

int main() {
    // Test cases
    const char* testUrls[] = {
        "https://api.github.com/users/octocat",
        "https://jsonplaceholder.typicode.com/posts/1",
        "https://api.publicapis.org/entries",
        "https://api.openweathermap.org/data/2.5/weather?q=London&appid=test",
        "https://api.coindesk.com/v1/bpi/currentprice.json"
    };
    int numUrls = sizeof(testUrls) / sizeof(testUrls[0]);

    for (int i = 0; i < numUrls; i++) {
        printf("\\nTesting URL: %s\\n", testUrls[i]);
        struct json_object *json = fetchJsonFromUrl(testUrls[i]);
        
        if (json) {
            const char *json_str = json_object_to_json_string(json);
            printf("Successfully fetched JSON: %.100s...\\n", json_str);
            json_object_put(json);  // Free JSON object
        } else {
            printf("Failed to fetch JSON\\n");
        }
    }

    return 0;
}
