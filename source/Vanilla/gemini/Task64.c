#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <jansson.h> // Remember to install Jansson library

// Callback function for cURL to write data to a string
size_t write_callback(char *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    char **buffer = (char **)userp;
    *buffer = realloc(*buffer, strlen(*buffer) + realsize + 1);
    if (*buffer == NULL) {
        fprintf(stderr, "Out of memory!\n");
        return 0;
    }
    strncat(*buffer, contents, realsize);
    return realsize;
}


json_t* read_json_from_url(const char *url) {
    CURL *curl = curl_easy_init();
    char *buffer = (char*)malloc(1);
    buffer[0] = '\0'; // Initialize as empty string

    json_t *root = NULL;
    json_error_t error;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        CURLcode res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
           root = json_loads(buffer, 0, &error);
           if (!root) {
               fprintf(stderr, "JSON parsing error: %s\n", error.text);
           }

        } else {
            fprintf(stderr, "cURL error: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }
    free(buffer);
    return root;
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Please provide a URL as a command line argument.\n");
        return 1;
    }

    char* url = argv[1];

    json_t *json_data = read_json_from_url(url);

    if (json_data) {
        char *json_string = json_dumps(json_data, JSON_INDENT(2));
        printf("%s\n", json_string);
        free(json_string);
        json_decref(json_data);
    }

    return 0;
}