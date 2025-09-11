#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

int downloadFile(const char* server, const char* username, const char* password, const char* remoteFile, const char* localFile) {
    CURL* curl;
    FILE* file;
    CURLcode res;
    
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    
    if (curl) {
        file = fopen(localFile, "wb");
        if (!file) {
            curl_easy_cleanup(curl);
            return 0;
        }

        char ftpUrl[256];
        snprintf(ftpUrl, sizeof(ftpUrl), "ftp://%s/%s", server, remoteFile);
        
        curl_easy_setopt(curl, CURLOPT_URL, ftpUrl);
        curl_easy_setopt(curl, CURLOPT_USERNAME, username);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

        res = curl_easy_perform(curl);
        fclose(file);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            curl_easy_cleanup(curl);
            return 0;
        }
        
        curl_easy_cleanup(curl);
    }
    
    curl_global_cleanup();
    return 1;
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        printf("Usage: <program> <server> <username> <password> <remoteFile>\n");
        return 1;
    }

    const char* server = argv[1];
    const char* username = argv[2];
    const char* password = argv[3];
    const char* remoteFile = argv[4];
    const char* localFile = remoteFile;  // Download to the same name locally

    if (downloadFile(server, username, password, remoteFile, localFile)) {
        printf("File downloaded successfully.\n");
    } else {
        printf("Failed to download the file.\n");
    }

    return 0;
}