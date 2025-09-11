
#include <stdio.h>
#include <curl/curl.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return fwrite(ptr, size, nmemb, stream);
}

int download_from_ftp(const char* host, const char* user, const char* pass, const char* filename) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    char url[512];
    
    sprintf(url, "ftp://%s/%s", host, filename);
    
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(filename, "wb");
        
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_USERNAME, user);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, pass);
        
        res = curl_easy_perform(curl);
        
        curl_easy_cleanup(curl);
        fclose(fp);
        
        return (res == CURLE_OK);
    }
    return 0;
}

int main() {
    // Test cases
    download_from_ftp("ftp.example.com", "user1", "pass1", "file1.txt");
    download_from_ftp("ftp.test.com", "user2", "pass2", "data.csv");
    download_from_ftp("ftp.sample.net", "admin", "admin123", "report.pdf");
    download_from_ftp("ftp.demo.org", "ftpuser", "ftppass", "backup.zip");
    download_from_ftp("ftp.secure.com", "root", "rootpass", "config.xml");
    
    return 0;
}
