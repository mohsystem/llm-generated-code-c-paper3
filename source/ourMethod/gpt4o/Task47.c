#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <curl/curl.h>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((char*)userp)[size * nmemb] = '\0';
    strncat(userp, contents, size * nmemb);
    return size * nmemb;
}

void scrape_and_store(const char* url) {
    sqlite3* db;
    sqlite3_open("localdata.db", &db);
    char* errMsg = 0;
    sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS data (title TEXT)", 0, 0, &errMsg);

    CURL* curl;
    CURLcode res;
    char readBuffer[1024] = {0};

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    // Example: simplistic parsing for <h1> tags
    char* start = strstr(readBuffer, "<h1>");
    while (start) {
        start += 4;
        char* end = strstr(start, "</h1>");
        if (!end) break;
        *end = '\0';
        char sql[256];
        snprintf(sql, sizeof(sql), "INSERT INTO data (title) VALUES ('%s')", start);
        sqlite3_exec(db, sql, 0, 0, &errMsg);
        start = strstr(end + 5, "<h1>");
    }

    sqlite3_close(db);
}

int main() {
    scrape_and_store("http://example.com");
    scrape_and_store("http://example.org");
    scrape_and_store("http://example.net");
    scrape_and_store("http://example.edu");
    scrape_and_store("http://example.gov");
    return 0;
}