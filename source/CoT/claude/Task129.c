
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <ctype.h>

struct MemoryStruct {
    char* memory;
    size_t size;
};

static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct* mem = (struct MemoryStruct*)userp;

    char* ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) {
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

int isValidFileName(const char* fileName) {
    if (!fileName) return 0;
    
    // Check for path traversal attempts
    if (strstr(fileName, "..") || strchr(fileName, '/') || strchr(fileName, '\\\\')) {\n        return 0;\n    }\n    \n    // Check for valid characters\n    while (*fileName) {\n        if (!isalnum(*fileName) && *fileName != '.' && *fileName != '_' && *fileName != '-') {
            return 0;
        }
        fileName++;
    }
    
    return 1;
}

char* retrieveFile(const char* fileName, const char* serverUrl) {
    if (!fileName || !serverUrl || !strlen(fileName) || !strlen(serverUrl)) {
        return strdup("Invalid input parameters");
    }

    // Validate filename for security
    if (!isValidFileName(fileName)) {
        return strdup("Invalid filename");
    }

    CURL* curl = curl_easy_init();
    struct MemoryStruct chunk = {malloc(1), 0};
    char* result;

    if (curl) {
        char* escapedFileName = curl_easy_escape(curl, fileName, strlen(fileName));
        char* url = malloc(strlen(serverUrl) + strlen(escapedFileName) + 1);
        if (!url) {
            curl_free(escapedFileName);
            free(chunk.memory);
            return strdup("Memory allocation error");
        }
        
        sprintf(url, "%s%s", serverUrl, escapedFileName);
        
        // Set secure CURL options
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
        
        CURLcode res = curl_easy_perform(curl);
        
        if (res != CURLE_OK) {
            result = strdup(curl_easy_strerror(res));
        } else {
            result = strdup(chunk.memory);
        }
        
        free(chunk.memory);
        free(url);
        curl_free(escapedFileName);
        curl_easy_cleanup(curl);
        
        return result;
    }

    free(chunk.memory);
    return strdup("CURL initialization failed");
}

int main() {
    // Test cases
    const char* serverUrl = "https://example.com/files/";
    char* result;
    
    result = retrieveFile("document.txt", serverUrl);
    printf("Test 1: %s\\n", result);
    free(result);
    
    result = retrieveFile("../sensitive.txt", serverUrl);
    printf("Test 2: %s\\n", result);
    free(result);
    
    result = retrieveFile("", serverUrl);
    printf("Test 3: %s\\n", result);
    free(result);
    
    result = retrieveFile("malicious;rm -rf.txt", serverUrl);
    printf("Test 4: %s\\n", result);
    free(result);
    
    result = retrieveFile("valid-document.pdf", serverUrl);
    printf("Test 5: %s\\n", result);
    free(result);
    
    return 0;
}
