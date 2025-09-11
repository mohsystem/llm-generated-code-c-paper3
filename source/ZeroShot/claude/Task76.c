
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <ctype.h>

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

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}

void extract_title(const char* html, char* title, size_t title_size) {
    char* lower_html = (char*)malloc(strlen(html) + 1);
    if(!lower_html) {
        strcpy(title, "Error: Memory allocation failed");
        return;
    }

    // Convert to lowercase for case-insensitive search
    size_t i;
    for(i = 0; html[i]; i++) {
        lower_html[i] = tolower(html[i]);
    }
    lower_html[i] = '\\0';

    char* title_start = strstr(lower_html, "<title>");
    char* title_end = strstr(lower_html, "</title>");

    if(title_start && title_end) {
        title_start += 7; // Skip "<title>"
        size_t title_length = title_end - title_start;
        if(title_length < title_size) {
            size_t orig_pos = title_start - lower_html;
            strncpy(title, html + orig_pos, title_length);
            title[title_length] = '\\0';
        } else {
            strcpy(title, "Error: Title too long");
        }
    } else {
        strcpy(title, "Error: Title not found");
    }

    free(lower_html);
}

void get_page_title(const char* url, char* title, size_t title_size) {
    CURL* curl = curl_easy_init();
    if(curl) {
        struct MemoryStruct chunk;
        chunk.memory = malloc(MAX_BUFFER);
        chunk.size = 0;

        if(chunk.memory == NULL) {
            strcpy(title, "Error: Memory allocation failed");
            return;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

        CURLcode res = curl_easy_perform(curl);
        
        if(res != CURLE_OK) {
            snprintf(title, title_size, "Error: %s", curl_easy_strerror(res));
        } else {
            extract_title(chunk.memory, title, title_size);
        }

        free(chunk.memory);
        curl_easy_cleanup(curl);
    } else {
        strcpy(title, "Error: Could not initialize CURL");
    }
}

int main(int argc, char* argv[]) {
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Test cases
    const char* test_urls[] = {
        "https://www.example.com",
        "https://www.google.com",
        "https://www.github.com",
        "https://www.wikipedia.org",
        "https://www.microsoft.com"
    };

    char title[MAX_TITLE];
    for(int i = 0; i < 5; i++) {
        printf("URL: %s\\n", test_urls[i]);
        get_page_title(test_urls[i], title, MAX_TITLE);
        printf("Title: %s\\n\\n", title);
    }

    curl_global_cleanup();
    return 0;
}
