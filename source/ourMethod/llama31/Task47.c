#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <sqlite3.h>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((char*)userp)[size * nmemb] = '\0';
    strcat((char*)userp, (char*)contents);
    return size * nmemb;
}

void scrapeAndSave(const char *url, const char *dbPath) {
    CURL *curl;
    CURLcode res;
    char readBuffer[1024*1024] = {0};

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, readBuffer);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L); // Add timeout to avoid CWE-1088
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "cURL error: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    // Simplified HTML parsing (use a library like gumbo-parser for real parsing)
    char *pos = strstr(readBuffer, "<a href=\"");
    char links[1024][1024];
    int linkCount = 0;
    while (pos != NULL) {
        char *endPos = strstr(pos + 9, "\"");
        if (endPos != NULL) {
            strncpy(links[linkCount], pos + 9, endPos - pos - 9);
            links[linkCount][endPos - pos - 9] = '\0';
            linkCount++;
            pos = endPos;
        } else {
            break;
        }
    }

    // Save to SQLite database
    sqlite3 *db;
    char *errMsg = NULL;
    int rc = sqlite3_open(dbPath, &db);
    if (rc) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS links (link TEXT)", NULL, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, "INSERT INTO links (link) VALUES (?)", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL prepare error: %s\n", sqlite3_errmsg(db));
        return;
    }

    for (int i = 0; i < linkCount; i++) {
        sqlite3_bind_text(stmt, 1, links[i], -1, SQLITE_STATIC);
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            fprintf(stderr, "SQL insert error: %s\n", sqlite3_errmsg(db));
        }
        sqlite3_reset(stmt);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    const char *url = "http://example.com";
    const char *dbPath = "example.db";
    scrapeAndSave(url, dbPath);
    return 0;
}