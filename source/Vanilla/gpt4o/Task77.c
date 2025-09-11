#include <stdio.h>
#include <curl/curl.h>

int download_file(const char *server, const char *user, const char *pass, const char *remote_filepath, const char *local_filepath) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        fp = fopen(local_filepath, "wb");
        if(!fp) {
            curl_easy_cleanup(curl);
            return 0;
        }
        char url[256];
        snprintf(url, sizeof(url), "ftp://%s/%s", server, remote_filepath);
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERNAME, user);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, pass);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        fclose(fp);
        curl_easy_cleanup(curl);
        return res == CURLE_OK;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 6) {
        printf("Usage: %s <server> <user> <pass> <remoteFilePath> <localFilePath>\n", argv[0]);
        return 1;
    }
    const char *server = argv[1];
    const char *user = argv[2];
    const char *pass = argv[3];
    const char *remote_filepath = argv[4];
    const char *local_filepath = argv[5];

    int success = download_file(server, user, pass, remote_filepath, local_filepath);
    printf("Download %s\n", success ? "successful" : "failed");
    return 0;
}