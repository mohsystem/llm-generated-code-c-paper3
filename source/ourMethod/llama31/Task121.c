#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>

size_t write_memory_callback(void *ptr, size_t size, size_t nmemb, void *data) {
    return size * nmemb;
}

int main() {
    CURL *curl;
    CURLcode res;
    FILE *fp;
    struct stat file_info;

    // Open the file
    fp = fopen("test.txt", "rb");
    if (fp == NULL) {
        printf("Couldn't open file\n");
        return 1;
    }

    // Get the file size
    if (fstat(fileno(fp), &file_info)) {
        printf("Couldn't get file size\n");
        return 1;
    }

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://example.com/upload");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_memory_callback);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_READDATA, fp);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)file_info.st_size);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }

    fclose(fp);
    curl_global_cleanup();

    return 0;
}