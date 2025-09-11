//  For C, handling HTML parsing and database interaction effectively requires external libraries.
//  This example demonstrates basic HTTP fetching using libcurl, but full scraping and DB storage
//  would necessitate integrating libraries like libxml2 (for HTML parsing) and sqlite3 (for database).  
//  This would increase the complexity significantly beyond a concise example.


#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

// Callback function to write received data to a buffer
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    char **buffer = (char **)userp;
    *buffer = (char *)realloc(*buffer, strlen(*buffer) + realsize + 1);
    if (*buffer == NULL) {
        fprintf(stderr, "Out of memory!\n");
        return 0;
    }
    strncat(*buffer, (char *)contents, realsize);
    return realsize;
}

void fetch_url(const char *url) {
    CURL *curl;
    CURLcode res;
    char *buffer = (char *)malloc(1); // Start with a small buffer
    buffer[0] = '\0'; // Initialize as empty string

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);


        res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
             // In a full implementation, you would parse the HTML in 'buffer' here 
             // (e.g., using libxml2) and store data in a database (e.g. sqlite3).
             // For this basic example, we just print the received data.
             printf("%s\n", buffer);
        } else {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }


        free(buffer);
        curl_easy_cleanup(curl);
    }
}

int main() {
    fetch_url("https://www.example.com");
    fetch_url("https://www.google.com");
    fetch_url("https://www.bing.com");
    fetch_url("https://www.wikipedia.org");
    fetch_url("https://www.yahoo.com");


    return 0;
}