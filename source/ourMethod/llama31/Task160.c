#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    char **response = (char **)userdata;
    *response = realloc(*response, strlen(*response) + size * nmemb + 1);
    strcat(*response, ptr);
    return size * nmemb;
}

int main() {
    char url[1024];
    printf("Enter the URL: ");
    fgets(url, sizeof(url), stdin);
    url[strcspn(url, "\n")] = 0; // Remove newline character

    CURL *curl;
    CURLcode res;
    char *response = malloc(1);
    *response = '\0';

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "cURL error: %s\n", curl_easy_strerror(res));
        } else {
            printf("Response: %s\n", response);
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    free(response);

    return 0;
}