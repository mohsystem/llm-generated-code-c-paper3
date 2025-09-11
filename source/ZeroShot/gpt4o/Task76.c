#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <regex.h>

struct MemoryStruct {
    char* memory;
    size_t size;
};

static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct* mem = (struct MemoryStruct*)userp;

    char* ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL) {
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

char* getPageTitle(const char* url) {
    CURL* curl_handle;
    CURLcode res;

    struct MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl_handle = curl_easy_init();

    if (curl_handle) {
        curl_easy_setopt(curl_handle, CURLOPT_URL, url);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)&chunk);
        curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "Mozilla/5.0");
        curl_easy_setopt(curl_handle, CURLOPT_TIMEOUT, 5L);

        res = curl_easy_perform(curl_handle);

        if (res == CURLE_OK) {
            regex_t regex;
            regmatch_t matches[2];
            if (regcomp(&regex, "<title>(.*?)</title>", REG_ICASE | REG_EXTENDED) == 0) {
                if (regexec(&regex, chunk.memory, 2, matches, 0) == 0) {
                    size_t start = matches[1].rm_so;
                    size_t end = matches[1].rm_eo;
                    size_t length = end - start;
                    char* title = (char*)malloc(length + 1);
                    if (title) {
                        strncpy(title, chunk.memory + start, length);
                        title[length] = '\0';
                        regfree(&regex);
                        curl_easy_cleanup(curl_handle);
                        free(chunk.memory);
                        curl_global_cleanup();
                        return title;
                    }
                }
                regfree(&regex);
            }
        }
        curl_easy_cleanup(curl_handle);
    }
    free(chunk.memory);
    curl_global_cleanup();
    return NULL;
}

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        char* title = getPageTitle(argv[i]);
        if (title) {
            printf("Title: %s\n", title);
            free(title);
        } else {
            printf("Failed to retrieve title for URL: %s\n", argv[i]);
        }
    }
    return 0;
}