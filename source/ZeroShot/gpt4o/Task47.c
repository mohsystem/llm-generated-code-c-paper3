#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <sqlite3.h>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((char*)userp)[size * nmemb] = '\0';
    return size * nmemb;
}

void scrapeAndStore(const char* url) {
    CURL* curl;
    CURLcode res;
    char readBuffer[8192] = {0};

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res == CURLE_OK) {
            sqlite3* db;
            if (sqlite3_open("sample.db", &db) == SQLITE_OK) {
                char* sql = "CREATE TABLE IF NOT EXISTS data (content TEXT);";
                char* errMsg = NULL;
                sqlite3_exec(db, sql, 0, 0, &errMsg);

                sql = "INSERT INTO data (content) VALUES (?);";
                sqlite3_stmt* stmt;
                sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

                sqlite3_bind_text(stmt, 1, readBuffer, -1, SQLITE_TRANSIENT);
                sqlite3_step(stmt);
                sqlite3_finalize(stmt);
                sqlite3_close(db);
            }
        }
    }
}

int main() {
    const char* url = "http://example.com"; // Test URL
    for (int i = 0; i < 5; i++) { // 5 test cases
        scrapeAndStore(url);
    }
    return 0;
}