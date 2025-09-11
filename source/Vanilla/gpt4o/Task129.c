#include <stdio.h>
#include <curl/curl.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((char*)userp) = strncat(((char*)userp), (char*)contents, size * nmemb);
    return size * nmemb;
}

char* fetchFileFromServer(const char* fileName) {
    CURL* curl;
    CURLcode res;
    static char readBuffer[10000] = {0};

    curl = curl_easy_init();
    if(curl) {
        char url[256];
        sprintf(url, "http://yourserver.com/files/%s", fileName);
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

int main() {
    printf("%s\n", fetchFileFromServer("file1.txt"));
    printf("%s\n", fetchFileFromServer("file2.txt"));
    printf("%s\n", fetchFileFromServer("file3.txt"));
    printf("%s\n", fetchFileFromServer("file4.txt"));
    printf("%s\n", fetchFileFromServer("file5.txt"));
    return 0;
}