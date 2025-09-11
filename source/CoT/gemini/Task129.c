#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <libgen.h>


size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}


void retrieveFile(const char *fileName, const char *serverUrl) {
    if (fileName == NULL || strlen(fileName) == 0 || strstr(fileName, "..") != NULL || strstr(fileName, "/") != NULL) {
         fprintf(stderr, "Invalid file name.\n");
         return;
    }

    if (serverUrl == NULL || strlen(serverUrl) == 0) {
        fprintf(stderr, "Invalid server URL.\n");
         return;
    }

    CURL *curl;
    FILE *fp;
    CURLcode res;
    char *url = (char *)malloc(strlen(serverUrl) + strlen(fileName) + 1);

    if (url == NULL) {
        perror("Memory allocation failed");
        return;
    }
    
    strcpy(url, serverUrl);
    strcat(url, fileName);


    curl = curl_easy_init();
    if (curl) {
        fp = fopen(fileName, "wb");
        if (fp) {
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            res = curl_easy_perform(curl);

             if (res != CURLE_OK) {
                fprintf(stderr, "Error retrieving file: %s\n", curl_easy_strerror(res));
            } else {
                printf("File %s downloaded successfully.\n", fileName);
            }
            fclose(fp);
        } else {
           perror("Error opening file for writing");
        }
        curl_easy_cleanup(curl);
    } else {
        fprintf(stderr, "Error initializing cURL.\n");
    }

    free(url);
}

int main() {
    retrieveFile("test1.txt", "https://www.example.com/");
    retrieveFile("test2.txt", "https://www.example.com/");
    retrieveFile("test3.pdf", "https://www.example.com/");
    retrieveFile("test4.jpg", "https://www.example.com/");
    retrieveFile("test5.doc", "https://www.example.com/");
    return 0;
}