#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((char*)userp) = realloc((char*)userp, size * nmemb + 1);
    strcat((char*)userp, (char*)contents);
    return size * nmemb;
}

void makeHttpRequest(const char* url) {
    CURL *curl;
    CURLcode res;
    char *readBuffer = malloc(1);

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "cURL error: %s\n", curl_easy_strerror(res));
        } else {
            long responseCode;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
            printf("URL: %s, Response Code: %ld\n", url, responseCode);
            if (responseCode == 200) {
                printf("Response: %s\n", readBuffer);
            }
        }
        curl_easy_cleanup(curl);
        free(readBuffer);
    }
    curl_global_cleanup();
}

int main() {
    const char* testUrls[] = {
        "http://example.com",
        "https://www.google.com",
        "http://localhost:8080/test.html",
        "https://www.github.com",
        "http://invalid-url"
    };

    for (int i = 0; i < 5; ++i) {
        makeHttpRequest(testUrls[i]);
    }

    return 0;
}