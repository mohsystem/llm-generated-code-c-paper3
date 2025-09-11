
// Note: This implementation requires libcurl and sqlite3 libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <sqlite3.h>

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;
    
    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) {
        printf("Not enough memory\\n");
        return 0;
    }
    
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    
    return realsize;
}

void create_table(sqlite3 *db) {
    char *err_msg = 0;
    const char *sql = "CREATE TABLE IF NOT EXISTS scraped_data ("
                     "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                     "title TEXT,"
                     "link TEXT);";
    
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\\n", err_msg);
        sqlite3_free(err_msg);
    }
}

void scrape_and_store(const char *url, sqlite3 *db) {
    CURL *curl = curl_easy_init();
    if (curl) {
        struct MemoryStruct chunk;
        chunk.memory = malloc(1);
        chunk.size = 0;
        
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        
        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            sqlite3_stmt *stmt;
            const char *sql = "INSERT INTO scraped_data (title, link) VALUES (?, ?)";
            
            sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
            sqlite3_bind_text(stmt, 1, "Raw HTML", -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, url, -1, SQLITE_STATIC);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        }
        
        curl_easy_cleanup(curl);
        free(chunk.memory);
    }
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("webscraper.db", &db);
    
    if (rc) {
        fprintf(stderr, "Can't open database: %s\\n", sqlite3_errmsg(db));
        return 1;
    }
    
    create_table(db);
    
    // Test cases
    const char *test_urls[] = {
        "https://example.com",
        "https://wikipedia.org",
        "https://github.com",
        "https://reddit.com",
        "https://news.ycombinator.com"
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Scraping: %s\\n", test_urls[i]);
        scrape_and_store(test_urls[i], db);
    }
    
    sqlite3_close(db);
    return 0;
}
