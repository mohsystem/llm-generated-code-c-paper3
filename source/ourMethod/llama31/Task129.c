#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main() {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    char fileName[256];

    printf("Enter the file name: ");
    fgets(fileName, sizeof(fileName), stdin);
    fileName[strcspn(fileName, "\n")] = 0; // Remove newline character

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        fp = fopen(fileName, "wb");
        if(fp == NULL) {
            fprintf(stderr, "Could not open file for writing.\n");
            return 1;
        }
        char url[256];
        snprintf(url, sizeof(url), "https://example.com/%s", fileName);
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "cURL error: %s\n", curl_easy_strerror(res));
        } else {
            printf("File downloaded successfully.\n");
        }
        fclose(fp);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return 0;
}