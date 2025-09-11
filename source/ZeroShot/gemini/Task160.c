#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// Callback function to write data to a string
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    char **response_ptr = (char **)userp;
    *response_ptr = (char *)realloc(*response_ptr, strlen(*response_ptr) + realsize + 1);
    if (*response_ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 0;  // Indicate failure
    }
    strcat(*response_ptr, (char *)contents);
    return realsize;
}


char* make_http_request(const char* url) {
    CURL *curl = curl_easy_init();
    if (curl) {
        char *response = (char *)malloc(1); // Initialize an empty string
        response[0] = '\0';

        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);


        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
             free(response);
            return "HTTP request failed";

        }


        curl_easy_cleanup(curl);
        return response;

    } else {
        return "Failed to initialize cURL";
    }

}


int main() {
    char *response;

    response = make_http_request("https://www.example.com");
    printf("Response: %s\n", response);
    free(response);


    response = make_http_request("https://www.google.com");
    printf("Response: %s\n", response);
    free(response);

    response = make_http_request("https://www.amazon.com");
    printf("Response: %s\n", response);
    free(response);


    response = make_http_request("https://www.wikipedia.org");
    printf("Response: %s\n", response);
    free(response);


    response = make_http_request("invalidurl");
    printf("Response: %s\n", response);
    free(response);

    return 0;
}