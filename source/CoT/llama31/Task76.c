#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((char*)userp)[size * nmemb] = '\0';
    return size * nmemb;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide the URL as a command line argument.\n");
        return 1;
    }
    CURL *curl;
    CURLcode res;
    char *url = argv[1];
    char readBuffer[1024];

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, readBuffer);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            printf("Failed to retrieve page title\n");
        } else {
            // Simple title extraction (not robust)
            char *titleStart = strstr(readBuffer, "<title>");
            if (titleStart != NULL) {
                char *titleEnd = strstr(titleStart + 7, "</title>");
                if (titleEnd != NULL) {
                    printf("Page Title: %.*s\n", titleEnd - titleStart - 7, titleStart + 7);
                }
            }
        }
        curl_easy_cleanup(curl);
    }
    return 0;
}