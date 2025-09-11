#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

// Callback function for cURL to write data to a string
size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    size_t realsize = size * nmemb;
    char** buffer = (char**)userdata;
    *buffer = (char*)realloc(*buffer, strlen(*buffer) + realsize + 1);
    if (*buffer == NULL) {
        fprintf(stderr, "Out of memory!\n");
        return 0;
    }
    strncat(*buffer, ptr, realsize);
    return realsize;
}

cJSON* read_json_from_url(const char* url_string) {
    CURL* curl = curl_easy_init();
    char* buffer = (char*)malloc(1); // Start with a small buffer
    buffer[0] = '\0';
    cJSON* json_object = NULL;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url_string);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            json_object = cJSON_Parse(buffer);
            if (!json_object) {
                const char *error_ptr = cJSON_GetErrorPtr();
                if (error_ptr != NULL) {
                    fprintf(stderr, "Error before: %s\n", error_ptr);
                }
            }

        }
        curl_easy_cleanup(curl);
    }
    free(buffer);
    return json_object;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Please provide a URL as a command-line argument.\n");
        return 1;
    }
    cJSON* json_object = read_json_from_url(argv[1]);
    if (json_object) {
        char* json_string = cJSON_Print(json_object);
        printf("%s\n", json_string);
        cJSON_Delete(json_object);
        free(json_string);
    }

    return 0;
}