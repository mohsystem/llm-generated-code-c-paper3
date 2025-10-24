
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <curl/curl.h>
#include <ctype.h>

#include "../../../../../../../usr/include/stdint.h"

/* Security: Maximum size limits to prevent memory exhaustion */
#define MAX_URL_LENGTH 2048
#define MAX_RESPONSE_SIZE (10 * 1024 * 1024)  /* 10MB */
#define MAX_TITLE_LENGTH 500
#define MAX_CONTENT_LENGTH 5000
#define MAX_DB_PATH_LENGTH 4096

/* Security: Structure to hold response data with size tracking */
typedef struct {
    char* data;
    size_t size;
    size_t capacity;
} ResponseBuffer;

/* Security: Initialize buffer - all pointers initialized, return checked */
ResponseBuffer* create_buffer(void) {
    ResponseBuffer* buffer = (ResponseBuffer*)calloc(1, sizeof(ResponseBuffer));
    if (!buffer) {
        return NULL;
    }
    
    buffer->capacity = 8192;
    buffer->data = (char*)malloc(buffer->capacity);
    if (!buffer->data) {
        free(buffer);
        return NULL;
    }
    
    buffer->size = 0;
    buffer->data[0] = '\0';  /* Security: Null-terminate */
    return buffer;
}

/* Security: Free buffer and clear sensitive data */
void free_buffer(ResponseBuffer* buffer) {
    if (buffer) {
        if (buffer->data) {
            /* Security: Clear memory before freeing */
            memset(buffer->data, 0, buffer->capacity);
            free(buffer->data);
        }
        free(buffer);
    }
}

/* Security: CURL callback with bounds checking and overflow protection */
static size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
    /* Security: Check for integer overflow in multiplication */
    if (size > 0 && nmemb > SIZE_MAX / size) {
        return 0;
    }
    
    size_t total_size = size * nmemb;
    ResponseBuffer* buffer = (ResponseBuffer*)userp;
    
    /* Security: Validate buffer pointer */
    if (!buffer || !buffer->data) {
        return 0;
    }
    
    /* Security: Check if adding data would exceed max size */
    if (buffer->size + total_size > MAX_RESPONSE_SIZE) {
        return 0;
    }
    
    /* Security: Grow buffer if needed - check for overflow */
    if (buffer->size + total_size >= buffer->capacity) {
        size_t new_capacity = buffer->capacity * 2;
        if (new_capacity > MAX_RESPONSE_SIZE) {
            new_capacity = MAX_RESPONSE_SIZE;
        }
        
        /* Security: Check realloc return value */
        char* new_data = (char*)realloc(buffer->data, new_capacity);
        if (!new_data) {
            return 0;
        }
        
        buffer->data = new_data;
        buffer->capacity = new_capacity;
    }
    
    /* Security: Bounds-checked copy */
    memcpy(buffer->data + buffer->size, contents, total_size);
    buffer->size += total_size;
    buffer->data[buffer->size] = '\0';  /* Security: Null-terminate */
    
    return total_size;
}

/* Security: Validate URL - only HTTPS, check length and characters */
int validate_url(const char* url) {
    if (!url) {
        return 0;
    }
    
    size_t len = strlen(url);
    
    /* Security: Check length bounds */
    if (len == 0 || len > MAX_URL_LENGTH) {
        return 0;
    }
    
    /* Security: Only allow HTTPS URLs */
    if (strncmp(url, "https://", 8) != 0) {
        return 0;
    }
    
    /* Security: Check for control characters */
    for (size_t i = 0; i < len; i++) {
        if (url[i] < 32 || url[i] == 127) {
            return 0;
        }
    }
    
    return 1;
}

/* Security: Sanitize text - remove control characters, enforce length limit */
char* sanitize_text(const char* input, size_t max_len) {
    if (!input) {
        return NULL;
    }
    
    size_t input_len = strlen(input);
    size_t safe_len = input_len < max_len ? input_len : max_len;
    
    /* Security: Allocate with size check */
    char* output = (char*)malloc(safe_len + 1);
    if (!output) {
        return NULL;
    }
    
    size_t j = 0;
    /* Security: Bounds-checked copy with character validation */
    for (size_t i = 0; i < input_len && j < safe_len; i++) {
        char c = input[i];
        /* Allow printable ASCII and common whitespace */
        if ((c >= 32 && c <= 126) || c == '\n' || c == '\r' || c == '\t') {
            output[j++] = c;
        }
    }
    
    output[j] = '\0';  /* Security: Null-terminate */
    return output;
}
/* Security: Scrape website using HTTPS with certificate verification */
int scrape_website(const char *url, ResponseBuffer *buffer) {
    CURL *curl = NULL;
    CURLcode res;

    /* Security: Validate inputs */
    if (!url || !buffer) {
        return 0;
    }

    if (!validate_url(url)) {
        fprintf(stderr, "Invalid URL\n");
        return 0;
    }

    /* Security: Initialize CURL - check return value */
    curl = curl_easy_init();
    if (!curl) {
        return 0;
    }

    /* Security: Configure CURL with security settings */
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);  /* Verify certificate chain */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);  /* Verify hostname */
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0L);  /* Don't follow redirects */
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);        /* Set timeout */
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 0L);

    /* Security: Perform request and check result */
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        fprintf(stderr, "CURL error: %s\n", curl_easy_strerror(res));
        return 0;
    }

    return 1;
}

/* Initialize database schema */
int init_database(sqlite3 *db) {
    char *err_msg = NULL;

    /* Security: Validate database pointer */
    if (!db) {
        return 0;
    }

    const char *sql =
        "CREATE TABLE IF NOT EXISTS scraped_data ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "url TEXT NOT NULL, "
        "title TEXT, "
        "content TEXT, "
        "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP);";

    /* Security: Check return value */
    int rc = sqlite3_exec(db, sql, NULL, NULL, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg ? err_msg : "Unknown");
        sqlite3_free(err_msg);
        return 0;
    }

    return 1;
}

/* Security: Store data using prepared statements to prevent SQL injection */
int store_data(sqlite3 *db, const char *url, const char *title, const char *content) {
    sqlite3_stmt *stmt = NULL;
    int rc;

    /* Security: Validate inputs */
    if (!db || !url || !title || !content) {
        return 0;
    }

    /* Security: Sanitize all inputs before storing */
    char *safe_url = sanitize_text(url, MAX_URL_LENGTH);
    char *safe_title = sanitize_text(title, MAX_TITLE_LENGTH);
    char *safe_content = sanitize_text(content, MAX_CONTENT_LENGTH);

    if (!safe_url || !safe_title || !safe_content) {
        free(safe_url);
        free(safe_title);
        free(safe_content);
        return 0;
    }

    const char *sql = "INSERT INTO scraped_data (url, title, content) VALUES (?, ?, ?);";

    /* Security: Prepare statement - check return value */
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        free(safe_url);
        free(safe_title);
        free(safe_content);
        return 0;
    }

    /* Security: Bind parameters - check all return values */
    rc = sqlite3_bind_text(stmt, 1, safe_url, -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) goto cleanup;

    rc = sqlite3_bind_text(stmt, 2, safe_title, -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) goto cleanup;

    rc = sqlite3_bind_text(stmt, 3, safe_content, -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) goto cleanup;

    /* Security: Execute statement - check return value */
    rc = sqlite3_step(stmt);
    rc = (rc == SQLITE_DONE) ? 1 : 0;

cleanup:
    /* Security: Clean up resources */
    sqlite3_finalize(stmt);
    free(safe_url);
    free(safe_title);
    free(safe_content);

    return rc;
}

/* Extract title from HTML - simple extraction with bounds checking */
char *extract_title(const char *html) {
    if (!html) {
        return strdup("No title found");
    }

    size_t html_len = strlen(html);
    /* Security: Limit search area to prevent excessive processing */
    size_t search_len = html_len < 10240 ? html_len : 10240;

    const char *start = NULL;
    const char *end = NULL;

    /* Security: Case-insensitive search with bounds checking */
    for (size_t i = 0; i < search_len - 7; i++) {
        if (strncasecmp(&html[i], "<title", 6) == 0) {
            /* Find end of opening tag */
            for (size_t j = i + 6; j < search_len; j++) {
                if (html[j] == '>') {
                    start = &html[j + 1];
                    break;
                }
            }
            break;
        }
    }

    if (start) {
        /* Find closing tag */
        for (size_t i = 0; start + i < html + search_len - 8; i++) {
            if (strncasecmp(start + i, "</title>", 8) == 0) {
                end = start + i;
                break;
            }
        }
    }

    if (start && end && end > start) {
        size_t title_len = end - start;
        if (title_len > MAX_TITLE_LENGTH) {
            title_len = MAX_TITLE_LENGTH;
        }

        /* Security: Allocate and copy with null termination */
        char *title = (char *)malloc(title_len + 1);
        if (title) {
            memcpy(title, start, title_len);
            title[title_len] = '\0';
            return title;
        }
    }

    return strdup("No title found");
}


/* Main scraping and storage function */
int scrape_and_store(const char* url, const char* db_path) {
    ResponseBuffer* buffer = NULL;
    sqlite3* db = NULL;
    char* title = NULL;
    int result = 0;
    
    /* Security: Validate inputs */
    if (!url || !db_path) {
        fprintf(stderr, "Invalid parameters\n");
        return 0;
    }
    
    if (strlen(db_path) > MAX_DB_PATH_LENGTH) {
        fprintf(stderr, "Database path too long\n");
        return 0;
    }
    
    /* Security: Create buffer - check return value */
    buffer = create_buffer();
    if (!buffer) {
        fprintf(stderr, "Failed to create buffer\n");
        return 0;
    }
    
    /* Scrape website */
    if (!scrape_website(url, buffer)) {
        fprintf(stderr, "Failed to scrape website\n");
        goto cleanup;
    }
    
    /* Extract title */
    title = extract_title(buffer->data);
    if (!title) {
        fprintf(stderr, "Failed to extract title\n");
        goto cleanup;
    }
    
    /* Security: Open database - check return value */
    if (sqlite3_open(db_path, &db) != SQLITE_OK) {
        fprintf(stderr, "Failed to open database\n");
        goto cleanup;
    }
    
    /* Initialize database */
    if (!init_database(db)) {
        fprintf(stderr, "Failed to initialize database\n");
        goto cleanup;
    }
    
    /* Store data */
    if (!store_data(db, url, title, buffer->data)) {
        fprintf(stderr, "Failed to store data\n");
        goto cleanup;
    }
    
    result = 1;
    
cleanup:
    /* Security: Clean up all resources */
    if (title) {
        free(title);
    }
    if (db) {
        sqlite3_close(db);
    }
    free_buffer(buffer);
    
    return result;
}

int main(void) {
    /* Security: Initialize CURL library once */
    curl_global_init(CURL_GLOBAL_DEFAULT);
    
    /* Test cases with HTTPS URLs */
    const char* test_urls[] = {
        "https://example.com",
        "https://www.ietf.org",
        "https://httpbin.org/html",
        "https://www.w3.org",
        "https://tools.ietf.org"
    };
    const char* db_path = "scraped_data.db";
    
    printf("Web Scraper - Test Cases\n");
    printf("========================\n\n");
    
    for (int i = 0; i < 5; i++) {
        printf("Test Case %d: %s\n", i + 1, test_urls[i]);
        int success = scrape_and_store(test_urls[i], db_path);
        printf("Result: %s\n\n", success ? "SUCCESS" : "FAILED");
    }
    
    /* Security: Cleanup CURL global state */
    curl_global_cleanup();
    
    return 0;
}
