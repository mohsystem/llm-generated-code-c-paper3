#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

// Callback function for writing received data to a file
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return fwrite(ptr, size, nmemb, stream);
}


char* retrieveFile(const char *fileName) {
    if (fileName == NULL || strlen(fileName) == 0) {
        return "File name cannot be empty.";
    }

    char *serverAddress = "http://example.com/files/"; // Replace with actual server address
    
    size_t serverLen = strlen(serverAddress);
    size_t fileLen = strlen(fileName);
    char *filePath = (char *)malloc(serverLen + fileLen + 1);
    if(filePath == NULL) {
        return "Memory allocation failed";
    }

    strcpy(filePath, serverAddress);
    strcat(filePath, fileName);



    CURL *curl;
    FILE *fp;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        fp = fopen(fileName, "wb"); // Save with user-provided name. Ensure file name is valid/safe
        if(fp == NULL) {
            curl_easy_cleanup(curl);
            free(filePath);
            return "File opening failed";
        }

        curl_easy_setopt(curl, CURLOPT_URL, filePath);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        res = curl_easy_perform(curl);
        
        fclose(fp);
        curl_easy_cleanup(curl);
        free(filePath);

        if (res == CURLE_OK) {
            return "File retrieved successfully.";
        } else {

            char* error_message = (char*) malloc(100 * sizeof(char));
            if (error_message != NULL) {
               snprintf(error_message, 100, "Error retrieving file: %s", curl_easy_strerror(res));
               return error_message;
            } else {
                return "Memory allocation failed for error message";
            }
        }
    } else {
        free(filePath);
        return "CURL initialization failed.";
    }

}

int main() {
    const char *testCases[] = {"test1.txt", "report.pdf", "image.jpg", "archive.zip", "document.docx"};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        char *result = retrieveFile(testCases[i]);
        printf("Test case: %s, Result: %s\n", testCases[i], result);
        if (strcmp(result, "File retrieved successfully.") != 0 && 
            strcmp(result, "File name cannot be empty.") != 0 &&
            strcmp(result, "Memory allocation failed") != 0 &&
            strcmp(result, "File opening failed") != 0 &&
            strcmp(result, "CURL initialization failed.") != 0 ) {
            free(result);
        }
    }

    return 0;
}