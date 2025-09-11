#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((char*)userp)[size * nmemb] = '\0';
    strcat((char*)userp, (char*)contents);
    return size * nmemb;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Please provide the URL as a command line argument.\n");
        return 1;
    }
    char* url = argv[1];
    CURL *curl;
    CURLcode res;
    char readBuffer[1024];

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, readBuffer);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "cURL error: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    // Simple JSON parsing (this is very basic and not robust)
    printf("%s\n", readBuffer);

    return 0;
}