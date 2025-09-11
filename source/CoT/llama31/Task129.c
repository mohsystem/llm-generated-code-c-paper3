#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void retrieveFile(const char *fileName) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    char url[256];
    sprintf(url, "http://example.com/%s", fileName);

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        fp = fopen(fileName, "wb");
        if(fp == NULL) {
            fprintf(stderr, "Could not open file for writing.\n");
            return;
        }
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "cURL error: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
        fclose(fp);
        printf("File retrieved successfully.\n");
    }
}

int main() {
    char fileName[256];
    printf("Enter the file name to retrieve: ");
    scanf("%255s", fileName);
    retrieveFile(fileName);
    return 0;
}