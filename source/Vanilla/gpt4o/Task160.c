#include <stdio.h>
#include <curl/curl.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((char*)userp)[size * nmemb] = '\0';
    strcat((char*)userp, (char*)contents);
    return size * nmemb;
}

void httpRequest(const char* url) {
    CURL* curl;
    CURLcode res;
    char buffer[10000] = {0};
    
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("%s\n", buffer);
        }
    }
}

int main() {
    httpRequest("http://www.example.com");
    httpRequest("http://www.google.com");
    httpRequest("http://www.github.com");
    httpRequest("http://www.stackoverflow.com");
    httpRequest("http://www.wikipedia.org");
    return 0;
}