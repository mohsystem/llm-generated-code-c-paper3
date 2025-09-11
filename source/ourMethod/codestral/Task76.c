// C does not have built-in support for HTTP requests and regular expressions.
// This code uses libcurl for HTTP requests and PCRE for regular expressions.
// To compile, use: gcc -o task76 task76.c -lcurl -lpcre

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <pcre.h>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    *(size_t*)userp += realsize;
    return realsize;
}

char* getPageTitle(const char* url) {
    CURL *curl;
    CURLcode res;
    char *readBuffer = NULL;
    size_t size = 0;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    const char *error;
    int erroffset;
    pcre *re;
    int ovector[30];

    re = pcre_compile("<title>(.+?)</title>", 0, &error, &erroffset, NULL);
    if (re == NULL) {
        printf("PCRE compilation failed at offset %d: %s\n", erroffset, error);
        return NULL;
    }

    int rc = pcre_exec(re, NULL, readBuffer, size, 0, 0, ovector, 30);
    if (rc < 0) {
        printf("PCRE execution failed: %d\n", rc);
        return NULL;
    }

    char *title = malloc(ovector[1] - ovector[0] + 1);
    strncpy(title, readBuffer + ovector[0], ovector[1] - ovector[0]);
    title[ovector[1] - ovector[0]] = '\0';

    free(readBuffer);
    pcre_free(re);

    return title;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide a URL as a command line argument.\n");
        return 1;
    }
    char* url = argv[1];
    char* title = getPageTitle(url);
    if (title) {
        printf("Page title: %s\n", title);
        free(title);
    } else {
        printf("An error occurred.\n");
    }
    return 0;
}