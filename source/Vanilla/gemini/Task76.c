#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <regex.h>

// Callback function for libcurl to write data to a string
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t realsize = size * nmemb;
    char **buffer = (char **)userdata;
    *buffer = (char *)realloc(*buffer, strlen(*buffer) + realsize + 1);
    if (*buffer == NULL) {
        fprintf(stderr, "Out of memory!\n");
        return 0; 
    }
    strncat(*buffer, ptr, realsize);
    return realsize;
}

char* extractTitle(const char *httpsUrl) {
    CURL *curl;
    CURLcode res;
    char *buffer = (char *)malloc(1); 
    buffer[0] = '\0';

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, httpsUrl);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            curl_easy_cleanup(curl);
            free(buffer);
            return strdup("Error fetching URL");
        }

        regex_t regex;
        regmatch_t match[2];
        int reti;
        char *title = NULL;
        reti = regcomp(&regex, "<title>(.*?)</title>", REG_EXTENDED);
        if (reti) {
            fprintf(stderr, "Could not compile regex\n");
            curl_easy_cleanup(curl);
            free(buffer);
             return strdup("Regex compilation error");
        }

        reti = regexec(&regex, buffer, 2, match, 0);
        if (!reti) {
            int start = match[1].rm_so;
            int end = match[1].rm_eo;
            title = (char *)malloc(end - start + 1);
            strncpy(title, buffer + start, end - start);
            title[end - start] = '\0';
        } else if (reti != REG_NOMATCH) {
            char msgbuf[100];
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        }


        regfree(&regex);
        curl_easy_cleanup(curl);
        free(buffer);

        if(title) return title; else return strdup("Title not found");

    }
    return strdup("Curl initialization error"); 
}

int main() {
    char *url1 = "https://www.example.com";
    char *url2 = "https://www.google.com";
    char *url3 = "https://www.amazon.com";
    char *url4 = "https://www.wikipedia.org";
    char *url5 = "https://www.youtube.com";

    printf("Title for %s: %s\n", url1, extractTitle(url1));
    printf("Title for %s: %s\n", url2, extractTitle(url2));
    printf("Title for %s: %s\n", url3, extractTitle(url3));
    printf("Title for %s: %s\n", url4, extractTitle(url4));
    printf("Title for %s: %s\n", url5, extractTitle(url5));
    
    return 0;
}