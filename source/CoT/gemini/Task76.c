#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <regex.h>


// Callback function for cURL to write data to a string
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


char* extract_title(const char *https_url) {
    CURL *curl = curl_easy_init();
    char *buffer = (char*)malloc(1);
    buffer[0] = '\0';
    char *title = NULL;


    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, https_url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

         CURLcode res = curl_easy_perform(curl);
        if(res == CURLE_OK) {

             regex_t regex;
            int reti;
            regmatch_t matches[2];


            reti = regcomp(&regex, "<title>(.*?)</title>", REG_EXTENDED|REG_ICASE);
             if (reti) {
                fprintf(stderr, "Could not compile regex\n");
                title = strdup("Error: Could not compile regex");
                goto cleanup;

            }

            reti = regexec(&regex, buffer, 2, matches, 0);
            if (!reti) {
                int start = matches[1].rm_so;
                int end = matches[1].rm_eo;
                title = (char*)malloc(end - start + 1);
                strncpy(title, buffer + start, end - start);
                title[end - start] = '\0';


            } else if (reti == REG_NOMATCH) {
                title = strdup("Title not found");
            } else {

                char msgbuf[100];
                regerror(reti, &regex, msgbuf, sizeof(msgbuf));
                fprintf(stderr, "Regex match failed: %s\n", msgbuf);
                title = strdup("Error: Regex match failed");
            }

            regfree(&regex);
        } else {

            title = (char *)malloc(100 * sizeof(char));
            snprintf(title, 100, "Error: %s", curl_easy_strerror(res));

        }


        cleanup:
        curl_easy_cleanup(curl);
        free(buffer);


    }
      return title;
}


int main() {
    char *test_cases[] = {
        "https://www.google.com",
        "https://www.example.com",
        "https://www.wikipedia.org",
        "https://www.amazon.com",
        "https://www.stackoverflow.com"
    };
    int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_test_cases; i++) {
        printf("URL: %s\n", test_cases[i]);
        char *title = extract_title(test_cases[i]);
         if (title) {
            printf("Title: %s\n", title);
            free(title);
        }
        printf("\n");
    }

    return 0;
}