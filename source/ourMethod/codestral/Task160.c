#include <stdio.h>
#include <curl/curl.h>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    *(char**)userp = realloc(*(char**)userp, realsize + 1);
    if (*(char**)userp == NULL) {
        fprintf(stderr, "Not enough memory (realloc returned NULL)\n");
        return 0;
    }

    memcpy(&(*(char**)userp)[realsize], contents, size * nmemb);
    (*(char**)userp)[realsize] = 0;
    return realsize;
}

char* send_http_request(const char* url) {
    CURL* curl;
    CURLcode res;
    char* readBuffer = NULL;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            exit(1);
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return readBuffer;
}

int main() {
    const char* test_urls[] = {"http://example.com", "https://www.google.com", "http://invalid-url.com", "https://secure-site.com"};
    int num_urls = sizeof(test_urls) / sizeof(test_urls[0]);

    for (int i = 0; i < num_urls; i++) {
        char* response = send_http_request(test_urls[i]);
        if (response) {
            printf("Response: %s\n", response);
            free(response);
        } else {
            fprintf(stderr, "Error sending HTTP request\n");
        }
    }

    return 0;
}