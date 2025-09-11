#include <stdio.h>
#include <string.h>
#include <curl/curl.h> // Make sure you have libcurl installed

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void retrieveFile(const char *fileName) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    char url[256]; // Adjust size as needed
    snprintf(url, sizeof(url), "http://example.com/%s", fileName); // Replace with your server URL

    curl = curl_easy_init();
    if (curl) {
        fp = fopen(fileName, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "Error downloading file: %s\n", curl_easy_strerror(res));
        } else {
            printf("File downloaded successfully: %s\n", fileName);
        }

        curl_easy_cleanup(curl);
        fclose(fp);
    } else {
        fprintf(stderr, "Error initializing cURL\n");
    }
}

int main() {
    retrieveFile("file1.txt");
    retrieveFile("file2.pdf");
    retrieveFile("image.jpg");
    retrieveFile("data.csv");
    retrieveFile("nonexistent_file.txt"); 
    return 0;
}