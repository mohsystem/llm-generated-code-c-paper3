#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <tidy/tidy.h>
#include <tidy/buffio.h>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((char*)userp) = realloc(((char*)userp), strlen((char*)userp) + size * nmemb + 1);
    strcat(((char*)userp), (char*)contents);
    return size * nmemb;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <URL>\n", argv[0]);
        return 1;
    }
    CURL *curl;
    CURLcode res;
    char *readBuffer = malloc(1);

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, readBuffer);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L); // Set a timeout to avoid CWE-1088
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "cURL error: %s\n", curl_easy_strerror(res));
        } else {
            TidyDoc tidyDoc;
            TidyBuffer tidyOutput;
            tidyBufferInit(&tidyOutput);
            tidyParseString(tidyDoc, readBuffer);
            tidyCleanAndRepair(tidyDoc);
            tidySaveBuffer(tidyDoc, &tidyOutput);
            TidyNode root = tidyGetRoot(tidyDoc);
            TidyNode child;
            for (child = tidyGetChild(root); child; child = tidyGetNext(child)) {
                if (tidyNodeIsHTMLElement(child, TidyTag_TITLE)) {
                    TidyBuffer buf;
                    tidyBufInit(&buf);
                    tidyNodeGetText(tidyDoc, child, &buf);
                    printf("%s\n", (const char *)buf.bp);
                    tidyBufFree(&buf);
                    break;
                }
            }
            tidyRelease(tidyDoc);
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    free(readBuffer);
    return 0;
}