#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

int downloadFileFromFTP(const char* hostname, const char* username, const char* password, const char* remoteFile) {
    CURL* curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        char url[256];
        snprintf(url, sizeof(url), "ftp://%s/%s", hostname, remoteFile);
        FILE* file = fopen(remoteFile, "wb");

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERNAME, username);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

        res = curl_easy_perform(curl);
        fclose(file);
        curl_easy_cleanup(curl);
        return res == CURLE_OK;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        printf("Usage: <hostname> <username> <password> <remoteFile>\n");
        return 1;
    }

    const char* hostname = argv[1];
    const char* username = argv[2];
    const char* password = argv[3];
    const char* remoteFile = argv[4];

    int success = downloadFileFromFTP(hostname, username, password, remoteFile);
    printf("Download %s\n", success ? "successful" : "failed");

    return 0;
}