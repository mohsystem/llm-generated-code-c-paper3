#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct string {
    char *ptr;
    size_t len;
};

void init_string(struct string *s) {
    s->len = 0;
    s->ptr = malloc(s->len+1);
    if (s->ptr == NULL) {
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s) {
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

char *get_page_title(const char *url) {
    CURL *curl;
    CURLcode res;
    struct string s;

    init_string(&s);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if(res == CURLE_OK) {
            char *title_start = strstr(s.ptr, "<title>");
            char *title_end = strstr(s.ptr, "</title>");
            if (title_start && title_end && title_end > title_start) {
                title_start += strlen("<title>");
                size_t title_length = title_end - title_start;
                char *title = (char*)malloc(title_length + 1);
                strncpy(title, title_start, title_length);
                title[title_length] = '\0';
                free(s.ptr);
                return title;
            }
        }
    }
    free(s.ptr);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Please provide a URL as a command line argument.\n");
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        char *title = get_page_title(argv[i]);
        printf("Title of %s: %s\n", argv[i], title ? title : "No title found");
        free(title);
    }
    return 0;
}