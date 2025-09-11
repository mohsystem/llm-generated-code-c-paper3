// This C code uses the libcurl library.
// You need to install libcurl to compile and run this code.
#include <stdio.h>
#include <curl/curl.h>

int main(int argc, char *argv[]) {
    if (argc < 5) {
        printf("Usage: %s <server> <username> <password> <file>\n", argv[0]);
        return 1;
    }

    CURL *curl;
    FILE *fp;
    CURLcode res;
    char url[100];

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        sprintf(url, "ftp://%s:%s@%s/%s", argv[2], argv[3], argv[1], argv[4]);

        fp = fopen(argv[4], "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
            fprintf(stderr, "download failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
        fclose(fp);
    }
    curl_global_cleanup();

    return 0;
}