#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <sqlite3.h>

// Requires libcurl and sqlite3
// On Debian/Ubuntu: sudo apt-get install libcurl4-openssl-dev libsqlite3-dev
// On Fedora/CentOS: sudo dnf install libcurl-devel sqlite-devel
//
// Compile with:
// gcc -std=c11 Task47.c -o task47 -lcurl -lsqlite3

// Struct to hold memory for libcurl response
struct MemoryStruct {
    char* memory;
    size_t size;
};

// Callback for libcurl to write data into our MemoryStruct
static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct* mem = (struct MemoryStruct*)userp;

    // Use realloc to expand the buffer. Check for allocation failure.
    char* ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL) {
        fprintf(stderr, "error: not enough memory (realloc returned NULL)\n");
        return 0; // Returning 0 will signal an error to libcurl
    }

    mem->memory = ptr;
    // Copy new data to the end of the existing buffer
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0; // Null-terminate the string

    return realsize;
}

// Function to parse the title from HTML content
// This is a very basic parser and not robust for complex HTML.
char* parse_title(const char* html) {
    const char* h1_start_tag_upper = "<H1";
    const char* h1_start_tag_lower = "<h1";
    const char* h1_end_tag_upper = "</H1>";
    const char* h1_end_tag_lower = "</h1>";

    const char* start_ptr = strstr(html, h1_start_tag_lower);
    if (!start_ptr) {
        start_ptr = strstr(html, h1_start_tag_upper);
    }
    if (!start_ptr) {
        return NULL;
    }

    // Find the closing '>' of the opening tag
    const char* tag_end_ptr = strchr(start_ptr, '>');
    if (!tag_end_ptr) {
        return NULL;
    }

    const char* content_start = tag_end_ptr + 1;
    
    const char* end_ptr = strstr(content_start, h1_end_tag_lower);
     if (!end_ptr) {
        end_ptr = strstr(content_start, h1_end_tag_upper);
    }
    if (!end_ptr) {
        return NULL;
    }

    size_t length = end_ptr - content_start;
    char* title = malloc(length + 1);
    if (!title) {
        fprintf(stderr, "Failed to allocate memory for title\n");
        return NULL;
    }

    strncpy(title, content_start, length);
    title[length] = '\0';
    return title; // Caller must free this memory
}

// Function to initialize the database table
int initialize_database(sqlite3* db) {
    const char* sql = "CREATE TABLE IF NOT EXISTS pages ("
                      " id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      " url TEXT NOT NULL UNIQUE,"
                      " title TEXT NOT NULL,"
                      " scraped_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
                      ");";
    char* err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 0;
    }
    return 1;
}

// Main function to scrape and store data
int scrape_and_store(const char* url, const char* db_path) {
    CURL* curl_handle = NULL;
    sqlite3* db = NULL;
    sqlite3_stmt* stmt = NULL;
    int exit_code = 0;

    struct MemoryStruct chunk;
    chunk.memory = malloc(1); // Start with 1 byte, will be grown by realloc
    if (chunk.memory == NULL) {
        fprintf(stderr, "Failed to allocate initial memory\n");
        return 0;
    }
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();
    if (!curl_handle) {
        fprintf(stderr, "Failed to initialize CURL handle\n");
        goto cleanup;
    }

    // 1. Fetch website content
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)&chunk);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_TIMEOUT, 20L);

    CURLcode res = curl_easy_perform(curl_handle);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        goto cleanup;
    }

    // 2. Parse data
    char* title = parse_title(chunk.memory);
    const char* final_title = title ? title : "No H1 Title Found";
    
    // 3. Store in database
    if (sqlite3_open(db_path, &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        if (title) free(title);
        goto cleanup;
    }

    if (!initialize_database(db)) {
        if (title) free(title);
        goto cleanup;
    }

    const char* sql = "INSERT OR REPLACE INTO pages (url, title) VALUES (?, ?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        if (title) free(title);
        goto cleanup;
    }

    sqlite3_bind_text(stmt, 1, url, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, final_title, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
        if (title) free(title);
        goto cleanup;
    }

    printf("Successfully scraped and stored: %s\n", url);
    exit_code = 1; // Success
    if (title) free(title);

cleanup:
    if (stmt) sqlite3_finalize(stmt);
    if (db) sqlite3_close(db);
    if (curl_handle) curl_easy_cleanup(curl_handle);
    if (chunk.memory) free(chunk.memory);
    curl_global_cleanup();
    
    return exit_code;
}

int main(void) {
    const char* db_file = "scraped_data_c.db";
    const char* urls_to_scrape[] = {
        "https://example.com/",
        "https://www.iana.org/domains/example",
        "https://httpbin.org/html",
        "http://info.cern.ch/hypertext/WWW/TheProject.html",
        "https://www.w3.org/TR/html52/"
    };
    int num_urls = sizeof(urls_to_scrape) / sizeof(urls_to_scrape[0]);
    int success_count = 0;

    printf("--- Starting Web Scraping Tests ---\n");
    for (int i = 0; i < num_urls; i++) {
        printf("Processing: %s\n", urls_to_scrape[i]);
        if (scrape_and_store(urls_to_scrape[i], db_file)) {
            success_count++;
        }
        printf("--------------------\n");
    }
    printf("--- Scraping Finished ---\n");
    printf("%d out of %d pages scraped successfully.\n", success_count, num_urls);
    printf("Data stored in '%s'\n", db_file);

    return 0;
}