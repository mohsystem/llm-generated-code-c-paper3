#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((char*)userp)[size * nmemb] = '\0';
    strncat((char*)userp, (char*)contents, size * nmemb);
    return size * nmemb;
}

void makeHttpRequest(const char* url) {
    CURL *curl;
    CURLcode res;
    char readBuffer[1024 * 10];

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, readBuffer);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "cURL error: %s\n", curl_easy_strerror(res));
        } else {
            long http_code = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
            printf("URL: %s, Response Code: %ld\n", url, http_code);
            printf("%s\n", readBuffer);
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

int main() {
    const char* urls[] = {
        "http://example.com",
        "http://www.google.com",
        "http://www.bbc.com",
        "http://www.github.com",
        "http://www.stackoverflow.com"
    };

    for (int i = 0; i < 5; i++) {
        makeHttpRequest(urls[i]);
    }

    return 0;
}