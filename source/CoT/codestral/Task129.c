#include <stdio.h>
#include <curl/curl.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void retrieve_file(const char* file_name, const char* url) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        fp = fopen(file_name, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        fclose(fp);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}

int main() {
    retrieve_file("example.txt", "http://example.com/example.txt");
    retrieve_file("image.jpg", "http://example.com/image.jpg");
    retrieve_file("document.pdf", "http://example.com/document.pdf");
    retrieve_file("data.csv", "http://example.com/data.csv");
    retrieve_file("program.exe", "http://example.com/program.exe");
    return 0;
}