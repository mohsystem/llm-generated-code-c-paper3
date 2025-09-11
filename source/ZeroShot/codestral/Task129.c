#include <stdio.h>
#include <curl/curl.h>

size_t write_data(void *ptr, size_t size, size_t nmeb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmeb, stream);
    return written;
}

void download_file(const char* file_name, const char* server_url) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    char url[256];
    snprintf(url, sizeof(url), "%s/%s", server_url, file_name);
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        fp = fopen(file_name, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        fclose(fp);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

int main() {
    try {
        download_file("test.txt", "http://example.com");
        // Add more test cases here
    } catch (...) {
        printf("An error occurred while downloading the file.\n");
    }
    return 0;
}