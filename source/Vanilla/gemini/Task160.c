#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    strcat((char*)userp, (char*)contents); 
    return realsize;
}

char* makeHttpRequest(char* url) {
    CURL *curl;
    CURLcode res;
    char *readBuffer = (char*)malloc(1024 * 1024); // Allocate 1MB buffer (adjust as needed)
    if (readBuffer == NULL) {
        perror("malloc failed");
        return "Error: Memory allocation failed.";
    }
    readBuffer[0] = '\0'; // Initialize as empty string


    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, readBuffer);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
             strcpy(readBuffer, "Error:");
            strcat(readBuffer, curl_easy_strerror(res));
           
        }
        curl_easy_cleanup(curl);
    } else {
         strcpy(readBuffer, "Error: Could not initialize cURL.");
    }
    return readBuffer;
}

int main() {
    char url[1024]; // Adjust size as needed

    printf("Enter a URL: ");
    scanf("%s", url);


    char* response = makeHttpRequest(url);
    printf("%s\n", response);
    free(response);

    response = makeHttpRequest("https://www.example.com");
    printf("%s\n", response);
    free(response);

    response = makeHttpRequest("https://www.google.com");
    printf("%s\n", response);
    free(response);


    response = makeHttpRequest("https://www.bing.com");
    printf("%s\n", response);
    free(response);


    response = makeHttpRequest("https://www.yahoo.com");
    printf("%s\n", response);
    free(response);


    response = makeHttpRequest("https://www.amazon.com");
    printf("%s\n", response);
    free(response);


    return 0;
}