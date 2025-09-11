#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <jansson.h>

struct string {
    char *ptr;
    size_t len;
};

void init_string(struct string *s) {
    s->len = 0;
    s->ptr = malloc(s->len + 1);
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

json_t *fetch_json_from_url(const char *url) {
    CURL *curl;
    CURLcode res;
    struct string s;
    json_t *json;
    json_error_t error;

    init_string(&s);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L); // Set timeout to 5 seconds
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            curl_easy_cleanup(curl);
            free(s.ptr);
            fprintf(stderr, "Failed to fetch JSON: %s\n", curl_easy_strerror(res));
            return NULL;
        }
        curl_easy_cleanup(curl);
    }

    json = json_loads(s.ptr, 0, &error);
    free(s.ptr);
    if (!json) {
        fprintf(stderr, "Error parsing JSON: %s\n", error.text);
        return NULL;
    }
    return json;
}

int main() {
    const char *testURLs[] = {
        "https://example.com/json1",
        "https://example.com/json2",
        "https://example.com/json3",
        "https://example.com/json4",
        "https://example.com/json5"
    };

    for (int i = 0; i < 5; ++i) {
        json_t *json = fetch_json_from_url(testURLs[i]);
        if (json) {
            char *jsonString = json_dumps(json, JSON_INDENT(4)); // Pretty print JSON
            printf("Fetched JSON from: %s\n%s\n", testURLs[i], jsonString);
            free(jsonString);
            json_decref(json);
        } else {
            fprintf(stderr, "Error fetching JSON from %s\n", testURLs[i]);
        }
    }
    return 0;
}