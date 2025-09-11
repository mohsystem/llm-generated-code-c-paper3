#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#ifdef _WIN32
#include <Windows.h>
#endif


// Callback function for cURL to write data to a file
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void download_and_execute(const char *url) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    char *filename = strrchr(url, '/') + 1;  // Extract filename from URL

    curl = curl_easy_init();
    if (curl) {
        fp = fopen(filename, "wb");
        if (fp) {
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            // Important: Set timeouts to avoid indefinite hanging
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L); // Example: 30-second timeout
            curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L); // Example: 10-second connect timeout

            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            }
            fclose(fp);


            // Execute downloaded file (Windows Example - Highly insecure. DO NOT USE in production without sandboxing or other security)
#ifdef _WIN32
             if ( (fp = fopen(filename, "r") ) != NULL) { //Check if file exists
                fclose(fp);
                ShellExecuteA(NULL, "open", filename, NULL, NULL, SW_SHOWDEFAULT);

                //remove(filename); // Optional: Remove after execution
            }
#endif

        } else {
            perror("fopen error");
        }
        curl_easy_cleanup(curl);
    }
}

int main() {

     // Test Cases (Replace with actual URLs, BUT BE EXTREMELY CAREFUL downloading and executing EXE files).
    const char *test_urls[] = {
        // "http://example.com/file1.exe", // Placeholder URL.  DO NOT USE without EXTREME caution.
        // "http://example.com/file2.exe", // Placeholder URL.  DO NOT USE without EXTREME caution.
        // "http://example.com/file3.exe", // Placeholder URL.  DO NOT USE without EXTREME caution.
        // "http://example.com/file4.exe", // Placeholder URL.  DO NOT USE without EXTREME caution.
        // "http://example.com/file5.exe"  // Placeholder URL.  DO NOT USE without EXTREME caution.
    };
    int num_test_cases = sizeof(test_urls) / sizeof(test_urls[0]);
    for (int i = 0; i < num_test_cases; i++) {
        printf("Test case (placeholder): %s\n", test_urls[i]);
    }
    printf("Test cases complete (placeholders used. No actual downloads/executions occurred)\n");


    return 0;
}