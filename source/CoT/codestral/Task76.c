#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <regex.h>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    strcat((char*)userp, (char*)contents);
    return size * nmemb;
}

char* get_page_title(const char* url) {
    CURL* curl;
    CURLcode res;
    char* readBuffer = malloc(1024 * 1024); // allocate 1MB
    if (!readBuffer) {
        fprintf(stderr, "Memory allocation error\n");
        return NULL;
    }
    readBuffer[0] = '\0';

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    regex_t regex;
    regmatch_t match;
    if (regcomp(&regex, "<title>(.*?)</title>", REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        free(readBuffer);
        return NULL;
    }
    if (regexec(&regex, readBuffer, 1, &match, 0)) {
        regfree(&regex);
        free(readBuffer);
        return "No title found";
    }
    char* title = malloc(match.rm_eo - match.rm_so + 1);
    if (!title) {
        fprintf(stderr, "Memory allocation error\n");
        regfree(&regex);
        free(readBuffer);
        return NULL;
    }
    memcpy(title, readBuffer + match.rm_so, match.rm_eo - match.rm_so);
    title[match.rm_eo - match.rm_so] = '\0';
    regfree(&regex);
    free(readBuffer);
    return title;
}

int main(int argc, char* argv[]) {
    if (argc < 6) {
        printf("Please provide 5 URLs as command line arguments.\n");
        return 1;
    }
    char* title;
    title = get_page_title(argv[1]);
    if (title) {
        printf("%s\n", title);
        free(title);
    }
    title = get_page_title(argv[2]);
    if (title) {
        printf("%s\n", title);
        free(title);
    }
    title = get_page_title(argv[3]);
    if (title) {
        printf("%s\n", title);
        free(title);
    }
    title = get_page_title(argv[4]);
    if (title) {
        printf("%s\n", title);
        free(title);
    }
    title = get_page_title(argv[5]);
    if (title) {
        printf("%s\n", title);
        free(title);
    }
    return 0;
}