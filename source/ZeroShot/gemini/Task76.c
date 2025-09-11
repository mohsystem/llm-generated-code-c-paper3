#include <stdio.h>
#include <string.h>
#include <curl/curl.h> // Requires libcurl

// Structure to hold the downloaded webpage content
struct MemoryStruct {
    char *memory;
    size_t size;
};

// Callback function for cURL to write data to memory
static size_t writeMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL) {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}


char* extractTitle(const char *url) {
    CURL *curl_handle;
    CURLcode res;
    struct MemoryStruct chunk;

    chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */
    chunk.size = 0;    /* no data at this point */

    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();


    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0"); // Set a user agent

    res = curl_easy_perform(curl_handle);

    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
         char *error_message = strdup("Error fetching URL");
        curl_easy_cleanup(curl_handle);
        curl_global_cleanup();
        free(chunk.memory);
        return error_message;
    }



    char *title = NULL;
    // Basic title extraction (improve with a proper HTML parser if needed)
    char *start = strstr(chunk.memory, "<title>");
    if (start) {
        start += 7; // Move past "<title>"
        char *end = strstr(start, "</title>");
        if (end) {
            size_t titleLen = end - start;
            title = (char *)malloc(titleLen + 1);
            strncpy(title, start, titleLen);
            title[titleLen] = '\0';
        }
    }
    

    curl_easy_cleanup(curl_handle);
    curl_global_cleanup();
    free(chunk.memory);
    
    if (!title) {
      return strdup("Title not found");
    }

    return title;
}



int main() {
     char *testUrls[] = {
        "https://www.example.com",
        "https://www.google.com",
        "https://www.amazon.com",
        "https://www.wikipedia.org",
        "https://www.invalidurl.com"
    };
    int numUrls = sizeof(testUrls) / sizeof(testUrls[0]);

    for (int i = 0; i < numUrls; i++) {
        char *title = extractTitle(testUrls[i]);
        printf("URL: %s, Title: %s\n", testUrls[i], title);
        free(title); // Free the allocated memory for the title
    }

    return 0;
}