#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <mysql/mysql.h>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((char*)userp)[size * nmemb] = '\0';
    strcat((char*)userp, (char*)contents);
    return size * nmemb;
}

void scrapeAndStore(const char *url, const char *dbHost, const char *dbUser, const char *dbPassword, const char *dbName) {
    CURL *curl;
    CURLcode res;
    char readBuffer[1024];

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, readBuffer);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "cURL error: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
    }

    // Parse HTML (simplified example)
    char *pos = strstr(readBuffer, "<p>");
    while (pos != NULL) {
        char *endPos = strstr(pos, "</p>");
        if (endPos != NULL) {
            char data[1024];
            strncpy(data, pos + 3, endPos - pos - 3);
            data[endPos - pos - 3] = '\0';

            // Store data in MySQL database
            MYSQL *conn;
            conn = mysql_init(0);
            if (conn == NULL) {
                fprintf(stderr, "mysql_init() failed\n");
                return;
            }
            if (!mysql_real_connect(conn, dbHost, dbUser, dbPassword, dbName, 0, NULL, 0)) {
                fprintf(stderr, "mysql_real_connect() failed\n");
                mysql_close(conn);
                return;
            }
            char query[1024];
            sprintf(query, "CREATE TABLE IF NOT EXISTS scraped_data (id INT AUTO_INCREMENT PRIMARY KEY, data TEXT)");
            mysql_query(conn, query);
            sprintf(query, "INSERT INTO scraped_data (data) VALUES ('%s')", data);
            mysql_query(conn, query);
            mysql_close(conn);

            pos = endPos + 4;  // Move to the next paragraph
        } else {
            break;
        }
    }
}

int main() {
    const char *url = "http://example.com";
    const char *dbHost = "localhost";
    const char *dbUser = "root";
    const char *dbPassword = "password";
    const char *dbName = "scraped_data";
    scrapeAndStore(url, dbHost, dbUser, dbPassword, dbName);
    return 0;
}