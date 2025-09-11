// Requires additional libraries (e.g., libcurl, a database library)
// and comprehensive error handling for production use. This C example
// is very basic and focuses primarily on demonstrating how libcurl and SQLite
// might be used together in a simplified scenario.  A robust example
// would use prepared statements, comprehensive error checks, and
// more advanced HTML parsing.

#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <sqlite3.h>

// Callback function for libcurl
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t realsize = size * nmemb;
    strcat((char*)userdata, ptr);  // Unsafe in general; for demo only
    return realsize;
}


void scrape_and_store(const char* website_url, const char* db_file) {
    CURL *curl;
    CURLcode res;
    char buffer[200000]; // Large buffer – dangerous in real code

    buffer[0] = '\0'; // Initialize as empty string

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, website_url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);  // buffer overflow risk
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if(res == CURLE_OK) {
            sqlite3 *db;
            char *zErrMsg = 0;
            int rc;

            rc = sqlite3_open(db_file, &db);
            if( rc ) {
                fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return;
            }

            // Very basic parsing - dangerous for real-world HTML!
            char *title_start = strstr(buffer, "<title>");
            if (title_start) {
                title_start += 7; // Move past "<title>"
                char *title_end = strstr(title_start, "</title>");
                if (title_end) {
                    *title_end = '\0'; // Null-terminate the title string
                    
                    // Create table
                    char create_table_sql[] = "CREATE TABLE IF NOT EXISTS scraped_data (title TEXT);";
                    rc = sqlite3_exec(db, create_table_sql, 0, 0, &zErrMsg);
                    if (rc != SQLITE_OK) {
                        fprintf(stderr, "SQL error: %s\n", zErrMsg);
                        sqlite3_free(zErrMsg);
                    }


                    //Insert title. Use prepared statements to avoid SQL injection in production.
                    char insert_sql[2048]; // Potential buffer overflow!
                    snprintf(insert_sql, sizeof(insert_sql), "INSERT INTO scraped_data (title) VALUES ('%s');", title_start);  // SQL injection risk!
                    rc = sqlite3_exec(db, insert_sql, 0, 0, &zErrMsg);

                    if( rc != SQLITE_OK ){
                        fprintf(stderr, "SQL error: %s\n", zErrMsg);
                        sqlite3_free(zErrMsg);
                    }
                }
            }
            sqlite3_close(db);
        } else {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

    } else {
      fprintf(stderr, "curl_easy_init() failed\n");
    }
}



int main() {
    char db_file[] = "mydatabase.db";
    scrape_and_store("https://www.example.com", db_file);
    scrape_and_store("https://www.google.com", db_file);
    scrape_and_store("https://www.wikipedia.org", db_file);
    scrape_and_store("https://www.amazon.com", db_file);
    scrape_and_store("https://www.cnn.com", db_file);

    return 0;
}