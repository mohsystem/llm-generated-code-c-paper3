#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <jansson.h>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    char **mem = (char**)userp;
    *mem = realloc(*mem, strlen(*mem) + realsize + 1);
    if (*mem == NULL) {
        fprintf(stderr, "Not enough memory (realloc returned NULL)\n");
        return 0;
    }
    strncat(*mem, (char*)contents, realsize);
    return realsize;
}

json_t* read_json_from_url(const char* url) {
    CURL *curl;
    CURLcode res;
    char *readBuffer = NULL;
    json_t *json_data = NULL;
    json_error_t error;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            goto cleanup;
        }
        json_data = json_loads(readBuffer, 0, &error);
        if (!json_data) {
            fprintf(stderr, "Error parsing JSON: %s\n", error.text);
        }
    }
cleanup:
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    free(readBuffer);
    return json_data;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Please provide a URL as a command line argument.\n");
        return 1;
    }
    json_t *json_data = read_json_from_url(argv[1]);
    if (json_data) {
        char *json_string = json_dumps(json_data, JSON_INDENT(2));
        printf("%s\n", json_string);
        free(json_string);
        json_decref(json_data);
    }
    return 0;
}