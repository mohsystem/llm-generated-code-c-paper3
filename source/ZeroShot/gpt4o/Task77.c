#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

int downloadFile(const char* hostname, const char* username, const char* password, const char* remoteFilePath) {
    CURL* curl;
    CURLcode res;
    char url[256];
    snprintf(url, sizeof(url), "ftp://%s%s", hostname, remoteFilePath);
    char localFilePath[256];
    snprintf(localFilePath, sizeof(localFilePath), "%s", strrchr(remoteFilePath, '/') + 1);

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        FILE* file = fopen(localFilePath, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERPWD, strcat(strcat(strdup(username), ":"), password));
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        res = curl_easy_perform(curl);
        fclose(file);
        curl_easy_cleanup(curl);
        return (res == CURLE_OK);
    }
    return 0;
}

int main() {
    // Test cases
    printf("%d\n", downloadFile("ftp.example.com", "user", "pass", "/path/to/sensitive/file1"));
    printf("%d\n", downloadFile("ftp.example.com", "user", "pass", "/path/to/sensitive/file2"));
    printf("%d\n", downloadFile("ftp.example.com", "user", "pass", "/path/to/sensitive/file3"));
    printf("%d\n", downloadFile("ftp.example.com", "user", "pass", "/path/to/sensitive/file4"));
    printf("%d\n", downloadFile("ftp.example.com", "user", "pass", "/path/to/sensitive/file5"));
    return 0;
}