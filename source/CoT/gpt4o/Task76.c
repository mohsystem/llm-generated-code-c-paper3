#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct string {
    char* ptr;
    size_t len;
};

void init_string(struct string* s) {
    s->len = 0;
    s->ptr = malloc(s->len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

size_t writefunc(void* ptr, size_t size, size_t nmemb, struct string* s) {
    size_t new_len = s->len + size * nmemb;
    s->ptr = realloc(s->ptr, new_len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "realloc() failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(s->ptr + s->len, ptr, size * nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;

    return size * nmemb;
}

char* getPageTitle(const char* url) {
    CURL* curl;
    CURLcode res;
    struct string s;
    init_string(&s);

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res == CURLE_OK) {
            char* titleStart = strstr(s.ptr, "<title>");
            char* titleEnd = strstr(s.ptr, "</title>");
            if (titleStart && titleEnd) {
                titleStart += 7;
                size_t titleLen = titleEnd - titleStart;
                char* title = malloc(titleLen + 1);
                strncpy(title, titleStart, titleLen);
                title[titleLen] = '\0';
                free(s.ptr);
                curl_global_cleanup();
                return title;
            }
        }
    }
    curl_global_cleanup();
    free(s.ptr);
    return "No Title Found";
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            char* title = getPageTitle(argv[i]);
            printf("URL: %s Title: %s\n", argv[i], title);
            free(title);
        }
    } else {
        printf("No URL provided.\n");
    }
    return 0;
}