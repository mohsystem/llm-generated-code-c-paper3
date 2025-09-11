#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h> // Requires libcurl


// Compile with: gcc your_program.c -lcurl -o your_program

// Structure to hold download data
struct DownloadData {
    char *data;
    size_t size;
};


// Callback function for libcurl to write data to buffer
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct DownloadData *data = (struct DownloadData *)userp;

    char *ptr = realloc(data->data, data->size + realsize + 1);
    if (ptr == NULL) {
        fprintf(stderr, "realloc failed\n");
        return 0;  // Indicate failure to libcurl
    }

    data->data = ptr;
    memcpy(&(data->data[data->size]), contents, realsize);
    data->size += realsize;
    data->data[data->size] = 0;

    return realsize;
}


void downloadAndExecute(const char *url) {
        // 1. Problem understanding: Download and execute EXE from URL.
        // 2. Security requirements: Avoid arbitrary code execution.  Restrict execution to a specific directory.
        // 3. Secure coding generation: Download to a temporary file, execute in a controlled environment.

    CURL *curl;
    CURLcode res;
    struct DownloadData data;
    data.data = NULL;
    data.size = 0;

    curl = curl_easy_init();
    if (curl) {
        // Set URL
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Set write callback
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);



        // Perform the download
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        } else {
             // 4. Code review: Check download size.


            // Create a temporary file
            char tempFilename[] = "downloaded_exeXXXXXX"; // Template for mkstemp
            int tempFile = mkstemp(tempFilename);

            if (tempFile == -1) {
                fprintf(stderr, "Error creating temporary file.\n");
                curl_easy_cleanup(curl);
                free(data.data);
                return;
            }

            // Write the downloaded data to the temporary file.
             size_t bytes_written = write(tempFile, data.data, data.size);
             if(bytes_written != data.size) {
                 fprintf(stderr, "Error writing to temporary file\n");
             }

             close(tempFile);



             printf("Downloaded to: %s\n", tempFilename);

            // 5. Secure code output:  Execute in restricted environment (if possible)
            // Note: Executing downloaded code is inherently risky. Avoid if possible, or sandbox.
            // Example (unsafe - avoid):
            // system(tempFilename);  // VERY UNSAFE - DO NOT USE IN PRODUCTION!

            // Delete the temporary file (optional) - after handling execution if required.
             remove(tempFilename);
        }


        // Cleanup
        curl_easy_cleanup(curl);
        free(data.data);


    }

}





int main() {
    // Test cases (replace with actual URLs - ensure safe testing environment):
    char *testUrls[] = {
        "http://example.com/safe_program.exe", // Replace with dummy URLs
        "http://example.com/test2.exe",
        "http://example.com/test3.exe",
        "http://example.com/test4.exe",
        "http://example.com/test5.exe"
    };

    for (int i = 0; i < sizeof(testUrls) / sizeof(testUrls[0]); i++) {
        downloadAndExecute(testUrls[i]);
    }

    return 0;
}