#include <stdio.h>
#include <curl/curl.h>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((char*)userp)[size * nmemb - 1] = '\0';
    strncpy((char*)userp, (char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    CURL *curl = curl_easy_init();
    if (curl) {
        char response[1024] = {0};
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "Error: %s\n", curl_easy_strerror(res));
        } else {
            printf("Response: %s\n", response);
        }
    } else {
        fprintf(stderr, "Error: Failed to initialize cURL\n");
    }
    return 0;
}