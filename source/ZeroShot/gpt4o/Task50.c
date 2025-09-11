#include <stdio.h>
#include <curl/curl.h>

char* uploadFile(const char* filePath, const char* serverUrl) {
    FILE* file = fopen(filePath, "rb");
    if (!file) {
        return "File not found.";
    }

    CURL* curl;
    CURLcode res;
    char* response;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, serverUrl);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_READDATA, file);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            response = "Failed to upload file. CURL error.";
        } else {
            response = "File uploaded successfully.";
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    fclose(file);
    return response;
}

int main() {
    printf("%s\n", uploadFile("path/to/file1.txt", "http://example.com/upload"));
    printf("%s\n", uploadFile("path/to/file2.txt", "http://example.com/upload"));
    printf("%s\n", uploadFile("path/to/file3.txt", "http://example.com/upload"));
    printf("%s\n", uploadFile("path/to/file4.txt", "http://example.com/upload"));
    printf("%s\n", uploadFile("path/to/file5.txt", "http://example.com/upload"));
    return 0;
}