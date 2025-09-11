#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((char*)userp)[strnlen((char*)userp, size * nmemb) + nmemb] = '\0';
    strncat(userp, (char*)contents, nmemb);
    return size * nmemb;
}

char* fetchFileFromServer(const char* serverUrl, const char* fileName) {
    CURL* curl;
    CURLcode res;
    char* readBuffer = malloc(10000);
    if (!readBuffer) return "Memory allocation failed.";

    curl = curl_easy_init();
    if(curl) {
        char url[1024];
        snprintf(url, sizeof(url), "%s/%s", serverUrl, fileName);
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, readBuffer);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if(res != CURLE_OK) {
            snprintf(readBuffer, 10000, "Error fetching file: %s", curl_easy_strerror(res));
        }
    } else {
        snprintf(readBuffer, 10000, "Failed to initialize CURL.");
    }
    return readBuffer;
}

int main() {
    const char* serverUrl = "http://example.com/files";
    printf("%s\n", fetchFileFromServer(serverUrl, "testfile1.txt"));
    printf("%s\n", fetchFileFromServer(serverUrl, "testfile2.txt"));
    printf("%s\n", fetchFileFromServer(serverUrl, "testfile3.txt"));
    printf("%s\n", fetchFileFromServer(serverUrl, "testfile4.txt"));
    printf("%s\n", fetchFileFromServer(serverUrl, "testfile5.txt"));
    return 0;
}