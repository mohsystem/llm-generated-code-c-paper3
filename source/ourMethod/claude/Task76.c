
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

    if (mem->size + realsize >= MAX_BUFFER) {
        fprintf(stderr, "Error: Response too large\\n");
        return 0;
    }

    char* ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) {
        fprintf(stderr, "Error: Out of memory\\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}

char* extract_title(const char* html) {
    static char title[MAX_TITLE];
    const char* title_start = strcasestr(html, "<title>");
    if (!title_start) return "No title found";

    title_start += 7;  // Skip "<title>"
    const char* title_end = strcasestr(title_start, "</title>");
    if (!title_end) return "No title found";

    size_t title_len = title_end - title_start;
    if (title_len >= MAX_TITLE) title_len = MAX_TITLE - 1;

    strncpy(title, title_start, title_len);
    title[title_len] = '\\0';
    return title;
}

char* get_page_title(const char* url) {
    if (!url || strncasecmp(url, "https://", 8) != 0) {
        return "Invalid URL: URL must start with https://";
    }

    CURL* curl = curl_easy_init();
    if (!curl) {
        return "Failed to initialize CURL";
    }

    struct MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);

    CURLcode res = curl_easy_perform(curl);
    char* result;

    if (res != CURLE_OK) {
        result = (char*)curl_easy_strerror(res);
    } else {
        result = extract_title(chunk.memory);
    }

    curl_easy_cleanup(curl);
    free(chunk.memory);
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <https_url>\\n", argv[0]);
        return 1;
    }

    char* title = get_page_title(argv[1]);
    printf("Page title: %s\\n", title);

    // Test cases
    const char* test_urls[] = {
        "https://www.example.com",
        "https://www.google.com",
        "https://www.github.com",
        "https://www.kernel.org",
        "https://www.microsoft.com"
    };

    for (int i = 0; i < 5; i++) {
        printf("\\nTesting URL: %s\\n", test_urls[i]);
        printf("Title: %s\\n", get_page_title(test_urls[i]));
    }

    return 0;
}
