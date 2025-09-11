
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <time.h>
#include <sys/stat.h>

#define MAX_URL_LENGTH 2048
#define MAX_FILENAME_LENGTH 256
#define MAX_FILE_SIZE 100000000 // 100MB

struct WriteData {
    FILE *fp;
    size_t size;
};

static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    struct WriteData *wd = (struct WriteData*)userdata;
    size_t written = fwrite(ptr, size, nmemb, wd->fp);
    wd->size += written;
    return written;
}

static int is_valid_url(const char* url) {
    return (strncmp(url, "https://drive.google.com", 23) == 0);
}

static void generate_temp_filename(char* filename, size_t size) {
    time_t t;
    srand((unsigned)time(&t));
    snprintf(filename, size, "download_%x%x%x%x.exe", 
             rand(), rand(), rand(), rand());
}

static int is_valid_exe(const char* filepath) {
    FILE* fp = fopen(filepath, "rb");
    if (!fp) return 0;

    struct stat st;
    if (stat(filepath, &st) != 0 || st.st_size > MAX_FILE_SIZE) {
        fclose(fp);
        return 0;
    }

    char header[2];
    size_t read = fread(header, 1, 2, fp);
    fclose(fp);

    return (read == 2 && header[0] == 'M' && header[1] == 'Z');
}

static int execute_file(const char* filepath) {
    #ifdef _WIN32
        return system(filepath);
    #else
        char cmd[MAX_FILENAME_LENGTH + 10];
        snprintf(cmd, sizeof(cmd), "chmod +x %s", filepath);
        system(cmd);
        return system(filepath);
    #endif
}

void Task86_download_and_execute(const char* url) {
    if (!url || !is_valid_url(url)) {
        fprintf(stderr, "Invalid URL provided\\n");
        return;
    }

    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to initialize CURL\\n");
        return;
    }

    char temp_path[MAX_FILENAME_LENGTH];
    char temp_filename[MAX_FILENAME_LENGTH];
    struct WriteData wd = {0};

    #ifdef _WIN32
        GetTempPath(MAX_FILENAME_LENGTH, temp_path);
    #else
        strcpy(temp_path, "/tmp/");
    #endif

    generate_temp_filename(temp_filename, sizeof(temp_filename));
    strcat(temp_path, temp_filename);

    FILE* fp = fopen(temp_path, "wb");
    if (!fp) {
        curl_easy_cleanup(curl);
        fprintf(stderr, "Failed to create temporary file\\n");
        return;
    }

    wd.fp = fp;
    wd.size = 0;

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &wd);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

    CURLcode res = curl_easy_perform(curl);
    fclose(fp);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        remove(temp_path);
        fprintf(stderr, "Download failed: %s\\n", curl_easy_strerror(res));
        return;
    }

    if (!is_valid_exe(temp_path)) {
        remove(temp_path);
        fprintf(stderr, "Invalid EXE file\\n");
        return;
    }

    execute_file(temp_path);
    remove(temp_path);
}

int main() {
    // Test cases
    const char* test_urls[] = {
        "https://drive.google.com/file1.exe",
        "https://drive.google.com/file2.exe",
        "https://drive.google.com/file3.exe",
        "https://drive.google.com/file4.exe",
        "https://drive.google.com/file5.exe"
    };

    for (int i = 0; i < 5; i++) {
        printf("Processing %s\\n", test_urls[i]);
        Task86_download_and_execute(test_urls[i]);
    }

    return 0;
}
