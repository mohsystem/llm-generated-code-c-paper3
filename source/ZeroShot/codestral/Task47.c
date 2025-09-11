// C code:
#include <stdio.h>
#include <sqlite3.h>
#include <curl/curl.h>
#include <gumbo.h>

// You will need to write functions to parse the HTML and to handle libcurl's write callback

int main() {
    const char* url = "http://example.com";
    // Use libcurl to fetch the HTML
    // ...

    // Parse the HTML with Gumbo
    GumboOutput* output = gumbo_parse(html);
    // Extract data from the output
    // ...

    // Connect to the database
    sqlite3* db;
    int rc = sqlite3_open("test.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    }

    // Insert data into the database
    // ...

    sqlite3_close(db);
    return 0;
}