#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

size_t write_memory_callback(void *ptr, size_t size, size_t nmemb, void *data) {
    FILE *file = (FILE*)data;
    fwrite(ptr, size, nmemb, file);
    return size * nmemb;
}

void downloadAndExecute(const char *url) {
    CURL *curl;
    CURLcode res;
    FILE *file = fopen("downloaded.exe", "wb");

    if (!file) {
        fprintf(stderr, "Could not open file for writing.\n");
        return;
    }

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_memory_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "Error downloading the file: %s\n", curl_easy_strerror(res));
        } else {
            curl_easy_cleanup(curl);
            fclose(file);

            // Execute the downloaded EXE file
            // Note: Executing EXE files can be dangerous and should be done with caution.
            // This example uses the system function which is generally discouraged due to security risks.
            // Consider using a more secure approach if possible.
            system("downloaded.exe");
        }
    }
    curl_global_cleanup();
}

int main() {
    const char *urls[] = {
        "http://example.com/program.exe",  // Replace with actual URLs
        "http://example.com/program2.exe",
        "http://example.com/program3.exe",
        "http://example.com/program4.exe",
        "http://example.com/program5.exe"
    };

    for (int i = 0; i < 5; ++i) {
        downloadAndExecute(urls[i]);
    }

    return 0;
}