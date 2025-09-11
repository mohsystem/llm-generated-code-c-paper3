#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <regex.h>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    strcat((char *)userp, (char *)contents);
    return size * nmemb;
}

char *get_page_title(const char *url) {
    CURL *curl;
    CURLcode res;
    char readBuffer[1024 * 1024] = {0}; // Assuming the page size is less than 1MB

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
    if (regcomp(&regex, "<title>(.*?)</title>", 0)) {
        fprintf(stderr, "Could not compile regex\n");
        return NULL;
    }

    regmatch_t match[2];
    if (regexec(&regex, readBuffer, 2, match, 0)) {
        fprintf(stderr, "No title found\n");
        return NULL;
    }

    char *title = malloc(match[1].rm_eo - match[1].rm_so + 1);
    memcpy(title, readBuffer + match[1].rm_so, match[1].rm_eo - match[1].rm_so);
    title[match[1].rm_eo - match[1].rm_so] = '\0';

    regfree(&regex);
    return title;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Please provide a URL\n");
        return 1;
    }
    char *title = get_page_title(argv[1]);
    if (title) {
        printf("%s\n", title);
        free(title);
    }
    return 0;
}