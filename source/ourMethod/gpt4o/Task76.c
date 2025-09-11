#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <regex.h>

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL) {
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

char* getPageTitle(const char* url) {
    CURL *curl_handle;
    CURLcode res;

    struct MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();

    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl_handle, CURLOPT_TIMEOUT, 5L);

    res = curl_easy_perform(curl_handle);

    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        return NULL;
    }

    curl_easy_cleanup(curl_handle);
    curl_global_cleanup();

    regex_t regex;
    regmatch_t pmatch[2];
    if (regcomp(&regex, "<title>(.*?)</title>", REG_ICASE | REG_EXTENDED) != 0) {
        return NULL;
    }

    if (regexec(&regex, chunk.memory, 2, pmatch, 0) == 0) {
        size_t title_length = pmatch[1].rm_eo - pmatch[1].rm_so;
        char *title = (char *)malloc(title_length + 1);
        strncpy(title, chunk.memory + pmatch[1].rm_so, title_length);
        title[title_length] = '\0';
        regfree(&regex);
        free(chunk.memory);
        return title;
    }

    regfree(&regex);
    free(chunk.memory);
    return NULL;
}

int main() {
    const char* testUrls[] = {
        "https://www.example.com",
        "https://www.google.com",
        "https://www.github.com",
        "https://www.stackoverflow.com",
        "https://www.wikipedia.org"
    };

    for (int i = 0; i < 5; i++) {
        char* title = getPageTitle(testUrls[i]);
        if (title) {
            printf("Title of %s: %s\n", testUrls[i], title);
            free(title);
        } else {
            printf("Failed to retrieve title for %s\n", testUrls[i]);
        }
    }

    return 0;
}