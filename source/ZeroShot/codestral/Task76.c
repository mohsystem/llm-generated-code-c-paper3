#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <regex.h>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    strncat((char*)userp, (char*)contents, size * nmemb);
    return size * nmemb;
}

char* getPageTitle(const char* url) {
    CURL *curl;
    CURLcode res;
    char readBuffer[2048] = {0};

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, readBuffer);
        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    regex_t regex;
    regmatch_t pmatch[1];
    if(regcomp(&regex, "<title>(.*?)</title>", REG_EXTENDED) != 0) {
        return NULL;
    }
    if(regexec(&regex, readBuffer, 1, pmatch, 0) == 0) {
        char *title = malloc(pmatch[1].rm_eo - pmatch[1].rm_so + 1);
        strncpy(title, readBuffer + pmatch[1].rm_so, pmatch[1].rm_eo - pmatch[1].rm_so);
        title[pmatch[1].rm_eo - pmatch[1].rm_so] = '\0';
        regfree(&regex);
        return title;
    }
    regfree(&regex);
    return NULL;
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        return 1;
    }
    char* title = getPageTitle(argv[1]);
    if(title) {
        printf("%s\n", title);
        free(title);
    }
    return 0;
}