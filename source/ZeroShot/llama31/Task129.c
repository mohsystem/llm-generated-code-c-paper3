#include <curl/curl.h>
#include <stdio.h>

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((char*)userp)[size * nmemb] = '\0';
    printf("%s", (char*)userp);
    return size * nmemb;
}

void retrieveFile(const char* fileName) {
    CURL *curl;
    CURLcode res;
    char buffer[1024];

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        snprintf(buffer, sizeof(buffer), "http://example.com/%s", fileName);
        curl_easy_setopt(curl, CURLOPT_URL, buffer);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

int main() {
    const char* fileNames[] = {"file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt"};
    for (int i = 0; i < 5; i++) {
        retrieveFile(fileNames[i]);
    }
    return 0;
}