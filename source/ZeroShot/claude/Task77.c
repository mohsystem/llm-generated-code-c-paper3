
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

size_t write_callback(void* ptr, size_t size, size_t nmemb, void* stream) {
    return fwrite(ptr, size, nmemb, (FILE*)stream);
}

int download_from_ftp(const char* server, const char* username, 
                     const char* password, const char* remote_file) {
    CURL* curl = curl_easy_init();
    if (!curl) return 0;

    // Extract filename from path
    const char* filename = strrchr(remote_file, '/');
    filename = filename ? filename + 1 : remote_file;

    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        curl_easy_cleanup(curl);
        return 0;
    }

    char url[512];
    snprintf(url, sizeof(url), "ftp://%s%s", server, remote_file);
    
    char userpwd[256];
    snprintf(userpwd, sizeof(userpwd), "%s:%s", username, password);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERPWD, userpwd);
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60L);

    CURLcode res = curl_easy_perform(curl);
    
    fclose(fp);
    curl_easy_cleanup(curl);
    
    return (res == CURLE_OK);
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("Usage: %s <server> <username> <password> <remoteFile>\\n", argv[0]);
        return 1;
    }

    // Test cases
    struct {
        const char* server;
        const char* username;
        const char* password;
        const char* remote_file;
    } test_cases[] = {
        {argv[1], argv[2], argv[3], argv[4]},
        {"ftp.example.com", "user1", "pass1", "/files/doc1.txt"},
        {"ftp.test.com", "user2", "pass2", "/secure/file2.pdf"},
        {"ftp.secure.com", "user3", "pass3", "/docs/report.docx"},
        {"ftp.company.com", "user4", "pass4", "/data/info.xlsx"}
    };

    for (int i = 0; i < 5; i++) {
        int result = download_from_ftp(
            test_cases[i].server,
            test_cases[i].username,
            test_cases[i].password,
            test_cases[i].remote_file
        );
        printf("Download %s for file: %s\\n", 
               result ? "successful" : "failed",
               test_cases[i].remote_file);
    }

    return 0;
}
