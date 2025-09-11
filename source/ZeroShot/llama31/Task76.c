// Note: This example uses libcurl but does not include HTML parsing.
// You need to install and link libcurl to compile this code.

#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((char*)userp)[size * nmemb] = '\0';
    strncat((char*)userp, (char*)contents, size * nmemb);
    return size * nmemb;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: ./program <URL>\n");
        return 1;
    }

    CURL *curl;
    CURLcode res;
    char readBuffer[1024];

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, readBuffer);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            printf("Request failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("%s\n", readBuffer); // This will print the raw HTML, not the title.
        }
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}