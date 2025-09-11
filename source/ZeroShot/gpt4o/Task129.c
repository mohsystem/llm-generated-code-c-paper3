#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    strncat(userp, contents, size * nmemb);
    return size * nmemb;
}

char* retrieveFileFromServer(const char* fileName) {
    static char readBuffer[10000];
    memset(readBuffer, 0, sizeof(readBuffer));
    char serverUrl[] = "http://example.com/files/"; // Replace with actual server URL
    CURL* curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
        char fullUrl[1024];
        snprintf(fullUrl, sizeof(fullUrl), "%s%s", serverUrl, fileName);
        curl_easy_setopt(curl, CURLOPT_URL, fullUrl);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if(res != CURLE_OK) {
            snprintf(readBuffer, sizeof(readBuffer), "Error: %s", curl_easy_strerror(res));
        }
    }
    return readBuffer;
}

int main() {
    printf("%s\n", retrieveFileFromServer("file1.txt"));
    printf("%s\n", retrieveFileFromServer("file2.txt"));
    printf("%s\n", retrieveFileFromServer("file3.txt"));
    printf("%s\n", retrieveFileFromServer("file4.txt"));
    printf("%s\n", retrieveFileFromServer("file5.txt"));
    return 0;
}