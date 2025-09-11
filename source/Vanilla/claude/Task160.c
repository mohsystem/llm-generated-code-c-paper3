
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
        fprintf(stderr, "malloc() failed\\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
{
    size_t new_len = s->len + size*nmemb;
    s->ptr = realloc(s->ptr, new_len+1);
    if (s->ptr == NULL) {
        fprintf(stderr, "realloc() failed\\n");
        exit(EXIT_FAILURE);
    }
    memcpy(s->ptr+s->len, ptr, size*nmemb);
    s->ptr[new_len] = '\\0';
    s->len = new_len;

    return size*nmemb;
}

char* makeHttpRequest(const char* url) {
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
        
        if(res != CURLE_OK) {
            return "Error: Could not perform request";
        }
        
        curl_easy_cleanup(curl);
        return s.ptr;
    }
    return "Error: Could not initialize CURL";
}

int main(void) {
    const char* urls[] = {
        "https://www.google.com",
        "https://www.github.com",
        "https://www.example.com",
        "https://api.github.com",
        "https://httpbin.org/get"
    };
    
    for(int i = 0; i < 5; i++) {
        printf("Testing URL: %s\\n", urls[i]);
        printf("%s\\n", makeHttpRequest(urls[i]));
        printf("------------------------\\n");
    }
    
    return 0;
}
