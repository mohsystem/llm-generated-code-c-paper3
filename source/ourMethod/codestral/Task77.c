#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <curl/curl.h>

size_t write_data(void *ptr, size_t size, size_t nmeb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmeb, stream);
    return written;
}

int download_file(const char* hostname, const char* username, const char* password, const char* remote_file) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    char *url;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        fp = fopen(remote_file, "wb");
        if (fp == NULL) {
            fprintf(stderr, "Error opening local file: %s\n", strerror(errno));
            return 1;
        }

        url = malloc(strlen(hostname) + strlen(username) + strlen(password) + strlen(remote_file) + 15);
        sprintf(url, "ftp://%s:%s@%s/%s", username, password, hostname, remote_file);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "Error downloading file: %s\n", curl_easy_strerror(res));
            fclose(fp);
            curl_easy_cleanup(curl);
            free(url);
            return 1;
        }

        printf("File downloaded successfully.\n");

        fclose(fp);
        curl_easy_cleanup(curl);
        free(url);
    }

    curl_global_cleanup();
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        printf("Usage: %s <hostname> <username> <password> <remote_file>\n", argv[0]);
        return 1;
    }

    const char* hostname = argv[1];
    const char* username = argv[2];
    const char* password = argv[3];
    const char* remote_file = argv[4];

    return download_file(hostname, username, password, remote_file);
}