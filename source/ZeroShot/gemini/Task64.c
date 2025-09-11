#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

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


cJSON *read_json_from_url(const char *url_string) {
    CURL *curl = curl_easy_init();
    char *buffer = (char *)malloc(1); // Start with a small buffer
    buffer[0] = '\0';
    cJSON *json_data = NULL;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url_string);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        CURLcode res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            json_data = cJSON_Parse(buffer);
            if (!json_data) {
                const char *error_ptr = cJSON_GetErrorPtr();
                if (error_ptr != NULL) {
                    fprintf(stderr, "Error parsing JSON: %s\n", error_ptr);
                }
            }
        } else {
            fprintf(stderr, "Error fetching URL: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);

    }
    free(buffer);
    return json_data;
}

int main(int argc, char *argv[]) {
  if (argc > 1) {
      const char *url_string = argv[1];
      cJSON *json_data = read_json_from_url(url_string);
      if (json_data) {
          char *json_string = cJSON_Print(json_data);
          printf("%s\n", json_string);
          free(json_string);
          cJSON_Delete(json_data);
      }

  } else {

      const char* test_urls[] = {
        "https://raw.githubusercontent.com/square/okhttp/master/okhttp/src/test/resources/ssl/certificate/cert.pem",
        "https://api.github.com/users/octocat",
        "https://jsonplaceholder.typicode.com/todos/1",
        "https://httpstat.us/200", // Might not be valid JSON
        "https://httpstat.us/404" // Will result in error
      };
      int num_urls = sizeof(test_urls) / sizeof(test_urls[0]);


      for (int i = 0; i < num_urls; i++) {
          printf("Testing URL: %s\n", test_urls[i]);
          cJSON *json_data = read_json_from_url(test_urls[i]);

          if (json_data) {
              char *json_string = cJSON_Print(json_data);
              printf("%s\n", json_string);
              free(json_string);
              cJSON_Delete(json_data);
          }
      }

  }
    return 0;
}