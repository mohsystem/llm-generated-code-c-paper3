// C code requires the installation of libcurl-dev package
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

size_t write_data(void *ptr, size_t size, size_t nmeb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmeb, stream);
    return written;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <hostname> <username> <password>\n", argv[0]);
        return 1;
    }

    const char *hostname = argv[1];
    const char *username = argv[2];
    const char *password = argv[3];

    CURL *curl;
    FILE *fp;
    CURLcode res;
    char *url;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        url = malloc(strlen(hostname) + strlen("ftp://") + 1);
        strcpy(url, "ftp://");
        strcat(url, hostname);

        fp = fopen("sensitive.txt", "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERPWD, (username + (char *)":" + password));
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("File has been downloaded successfully.\n");
        }

        curl_easy_cleanup(curl);
        fclose(fp);
        free(url);
    }

    curl_global_cleanup();
    return 0;
}