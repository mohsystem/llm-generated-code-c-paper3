// C language does not have built-in JSON parsing library.
// You need to use third-party libraries such as jansson, cJSON, etc.
// The following code uses cJSON library.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((char**)userp)[0] = realloc(((char**)userp)[0], strlen(((char**)userp)[0]) + size * nmemb + 1);
    strncat(((char**)userp)[0], (char*)contents, size * nmemb);
    return size * nmemb;
}

cJSON* readJsonFromUrl(const char* url) {
    CURL* curl;
    CURLcode res;
    char* readBuffer = malloc(1);

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    cJSON* json = cJSON_Parse(readBuffer);
    free(readBuffer);
    return json;
}

int main() {
    cJSON* json = readJsonFromUrl("https://example.com/test.json");
    printf("%s\n", cJSON_Print(json));
    cJSON_Delete(json);

    json = readJsonFromUrl("https://example.com/test2.json");
    printf("%s\n", cJSON_Print(json));
    cJSON_Delete(json);

    json = readJsonFromUrl("https://example.com/test3.json");
    printf("%s\n", cJSON_Print(json));
    cJSON_Delete(json);

    json = readJsonFromUrl("https://example.com/test4.json");
    printf("%s\n", cJSON_Print(json));
    cJSON_Delete(json);

    json = readJsonFromUrl("https://example.com/test5.json");
    printf("%s\n", cJSON_Print(json));
    cJSON_Delete(json);

    return 0;
}