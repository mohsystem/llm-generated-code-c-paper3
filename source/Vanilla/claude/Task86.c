
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
    FILE* fp = (FILE*)userp;
    size_t written = fwrite(contents, size, nmemb, fp);
    return written;
}

void download_and_execute(const char* url) {
    char filename[256];
    const char* last_slash = strrchr(url, '/');
    
    if(last_slash) {
        strcpy(filename, last_slash + 1);
    } else {
        strcpy(filename, "downloaded.exe");
    }
    
    // Download file using libcurl
    CURL* curl = curl_easy_init();
    if(curl) {
        FILE* fp = fopen(filename, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
        
        if(res == CURLE_OK) {
            // Execute file
            system(filename);
        }
    }
}

int main() {
    // Test cases - Note: Using dummy URLs for demonstration
    const char* test_urls[] = {
        "http://example.com/program1.exe",
        "http://example.com/program2.exe",
        "http://example.com/program3.exe",
        "http://example.com/program4.exe",
        "http://example.com/program5.exe"
    };
    
    for(int i = 0; i < 5; i++) {
        printf("Testing URL: %s\\n", test_urls[i]);
        download_and_execute(test_urls[i]);
    }
    
    return 0;
}
