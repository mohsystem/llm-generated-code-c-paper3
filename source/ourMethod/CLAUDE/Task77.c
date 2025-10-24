
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

#include "../../../../../../../../usr/include/stdint.h"

/* Maximum file size: 100MB to prevent resource exhaustion */
#define MAX_FILE_SIZE (100 * 1024 * 1024)
/* Maximum URL length to prevent buffer issues */
#define MAX_URL_LENGTH 2048
/* Maximum path length */
#define MAX_PATH_LENGTH 512

/* Secure memory cleanup - explicit zeroing that compiler cannot optimize away */
static void secure_zero(void *ptr, size_t len) {
    if (ptr == NULL || len == 0) return;
    volatile unsigned char *p = (volatile unsigned char *)ptr;
    while (len--) *p++ = 0;
}

/* Structure to hold download data with size limit enforcement */
struct download_buffer {
    unsigned char *data;
    size_t size;
    size_t capacity;
};

/* Write callback for curl - enforces size limits and validates data */
static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = 0;
    struct download_buffer *buf = (struct download_buffer *)userp;
    
    /* Validate inputs */
    if (contents == NULL || userp == NULL || size == 0 || nmemb == 0) {
        return 0;
    }
    
    /* Check for integer overflow in multiplication */
    if (nmemb > SIZE_MAX / size) {
        fprintf(stderr, "Error: Size calculation overflow\\n");
        return 0;
    }
    realsize = size * nmemb;
    
    /* Check if adding new data would exceed max file size */
    if (buf->size > MAX_FILE_SIZE || realsize > MAX_FILE_SIZE - buf->size) {
        fprintf(stderr, "Error: File size exceeds maximum allowed (%d bytes)\\n", MAX_FILE_SIZE);
        return 0;
    }
    
    /* Grow buffer if needed */
    if (buf->size + realsize > buf->capacity) {
        size_t new_capacity = buf->capacity * 2;
        if (new_capacity < buf->size + realsize) {
            new_capacity = buf->size + realsize;
        }
        /* Cap at maximum file size */
        if (new_capacity > MAX_FILE_SIZE) {
            new_capacity = MAX_FILE_SIZE;
        }
        
        unsigned char *new_data = (unsigned char *)realloc(buf->data, new_capacity);
        if (new_data == NULL) {
            fprintf(stderr, "Error: Memory allocation failed\\n");
            return 0;
        }
        buf->data = new_data;
        buf->capacity = new_capacity;
    }
    
    /* Copy data with bounds check */
    memcpy(buf->data + buf->size, contents, realsize);
    buf->size += realsize;
    
    return realsize;
}
/* Validate and sanitize filename to prevent path traversal */
static int validate_filename(const char *filename, char *safe_name, size_t safe_name_size) {
    size_t len = 0;
    size_t i = 0;

    if (filename == NULL || safe_name == NULL || safe_name_size == 0) {
        return -1;
    }

    len = strlen(filename);
    if (len == 0 || len >= safe_name_size) {
        return -1;
    }

    /* Reject paths with directory traversal attempts */
    if (strstr(filename, "..") != NULL ||
        strstr(filename, "/") != NULL ||
        strstr(filename, "\\") != NULL) {
        fprintf(stderr, "Error: Invalid filename - path traversal detected\n");
        return -1;
    }

    /* Copy only safe characters: alphanumeric, dash, underscore, dot */
    for (i = 0; i < len && i < safe_name_size - 1; i++) {
        char c = filename[i];
        if ((c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9') ||
            c == '_' || c == '-' || c == '.') {
            safe_name[i] = c;
        } else {
            fprintf(stderr, "Error: Invalid character in filename\n");
            return -1;
        }
    }
    safe_name[i] = '\0';

    /* Reject empty result or files starting with dot (hidden files) */
    if (safe_name[0] == '\0' || safe_name[0] == '.') {
        fprintf(stderr, "Error: Invalid filename\n");
        return -1;
    }

    return 0;
}

/* Securely write file using open-validate-write pattern to avoid TOCTOU */
static int secure_write_file(const char *filename, const unsigned char *data, size_t size) {
    int fd = -1;
    ssize_t written = 0;
    struct stat st;
    char temp_name[MAX_PATH_LENGTH];
    int ret = -1;

    if (filename == NULL || data == NULL || size == 0) {
        return -1;
    }

    /* Create temporary file name */
    ret = snprintf(temp_name, sizeof(temp_name), ".%s.tmp.XXXXXX", filename);
    if (ret < 0 || (size_t)ret >= sizeof(temp_name)) {
        fprintf(stderr, "Error: Filename too long\n");
        return -1;
    }

    /* Create temporary file with restrictive permissions (0600) and O_EXCL to prevent race */
    fd = mkstemp(temp_name);
    if (fd < 0) {
        fprintf(stderr, "Error: Cannot create temporary file: %s\n", strerror(errno));
        return -1;
    }

    /* Validate the opened file descriptor */
    if (fstat(fd, &st) != 0) {
        fprintf(stderr, "Error: Cannot stat temporary file\n");
        close(fd);
        unlink(temp_name);
        return -1;
    }

    /* Ensure it's a regular file */
    if (!S_ISREG(st.st_mode)) {
        fprintf(stderr, "Error: Not a regular file\n");
        close(fd);
        unlink(temp_name);
        return -1;
    }

    /* Write data in chunks with error checking */
    size_t total_written = 0;
    while (total_written < size) {
        written = write(fd, data + total_written, size - total_written);
        if (written < 0) {
            if (errno == EINTR) continue;
            fprintf(stderr, "Error: Write failed: %s\n", strerror(errno));
            close(fd);
            unlink(temp_name);
            return -1;
        }
        total_written += (size_t)written;
    }

    /* Flush to disk */
    if (fsync(fd) != 0) {
        fprintf(stderr, "Error: fsync failed: %s\n", strerror(errno));
        close(fd);
        unlink(temp_name);
        return -1;
    }

    close(fd);

    /* Atomic rename to target filename */
    if (rename(temp_name, filename) != 0) {
        fprintf(stderr, "Error: Cannot rename file: %s\n", strerror(errno));
        unlink(temp_name);
        return -1;
    }

    /* Set final restrictive permissions */
    if (chmod(filename, 0600) != 0) {
        fprintf(stderr, "Warning: Cannot set file permissions\n");
    }

    return 0;
}

/* Download file from FTP server with full security controls */
static int download_ftp_file(const char *hostname, const char *username,
                             const char *password, const char *remote_file,
                             const char *local_file) {
    CURL *curl = NULL;
    CURLcode res = CURLE_OK;
    char url[MAX_URL_LENGTH];
    char *encoded_file = NULL;
    struct download_buffer buffer = {NULL, 0, 0};
    int ret = -1;
    int snprintf_ret = 0;

    /* Validate all inputs - treat as untrusted */
    if (hostname == NULL || username == NULL || password == NULL ||
        remote_file == NULL || local_file == NULL) {
        fprintf(stderr, "Error: Invalid input parameters\n");
        return -1;
    }

    if (strlen(hostname) == 0 || strlen(remote_file) == 0 || strlen(local_file) == 0) {
        fprintf(stderr, "Error: Empty input parameters\n");
        return -1;
    }

    /* Initialize buffer with initial capacity */
    buffer.capacity = 4096;
    buffer.data = (unsigned char *)malloc(buffer.capacity);
    if (buffer.data == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return -1;
    }
    buffer.size = 0;

    /* Initialize curl */
    curl = curl_easy_init();
    if (curl == NULL) {
        fprintf(stderr, "Error: curl initialization failed\n");
        free(buffer.data);
        return -1;
    }

    /* URL encode the remote filename to handle special characters safely */
    encoded_file = curl_easy_escape(curl, remote_file, 0);
    if (encoded_file == NULL) {
        fprintf(stderr, "Error: Failed to encode filename\n");
        curl_easy_cleanup(curl);
        free(buffer.data);
        return -1;
    }

    /* Construct FTP URL - validate length to prevent overflow */
    snprintf_ret = snprintf(url, sizeof(url), "ftp://%s/%s", hostname, encoded_file);
    curl_free(encoded_file);

    if (snprintf_ret < 0 || (size_t)snprintf_ret >= sizeof(url)) {
        fprintf(stderr, "Error: URL too long\n");
        curl_easy_cleanup(curl);
        free(buffer.data);
        return -1;
    }

    /* Configure curl with secure options */
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_FTP);
    curl_easy_setopt(curl, CURLOPT_USERNAME, username);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_TRY);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
    curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 30L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 300L);
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 0L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0L);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

    /* Perform the download */
    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        fprintf(stderr, "Error: Download failed: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        secure_zero(buffer.data, buffer.size);
        free(buffer.data);
        return -1;
    }

    /* Verify we received data */
    if (buffer.size == 0) {
        fprintf(stderr, "Error: No data received\n");
        curl_easy_cleanup(curl);
        free(buffer.data);
        return -1;
    }

    /* Write to file securely */
    ret = secure_write_file(local_file, buffer.data, buffer.size);

    /* Clean up */
    curl_easy_cleanup(curl);

    /* Securely clear sensitive data from memory */
    secure_zero(buffer.data, buffer.size);
    free(buffer.data);

    if (ret == 0) {
        printf("File downloaded successfully to: %s\n", local_file);
        return 0;
    }

    return -1;
}

int main(int argc, char *argv[]) {
    char safe_remote_file[MAX_PATH_LENGTH];
    char safe_local_file[MAX_PATH_LENGTH];
    int result = 0;

    /* Validate argument count */
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <hostname> <username> <password> <remote_file>\n",
                argv[0] ? argv[0] : "program");
        fprintf(stderr, "Warning: Passing passwords via command line is insecure.\n");
        fprintf(stderr, "         Use environment variables or secure credential storage instead.\n");
        return 1;
    }

    /* Validate and sanitize remote filename */
    if (validate_filename(argv[4], safe_remote_file, sizeof(safe_remote_file)) != 0) {
        fprintf(stderr, "Error: Invalid remote filename\n");
        return 1;
    }

    /* Use sanitized filename as local filename */
    if (snprintf(safe_local_file, sizeof(safe_local_file), "%s", safe_remote_file) < 0 ||
        safe_local_file[0] == '\0') {
        fprintf(stderr, "Error: Invalid local filename\n");
        return 1;
    }

    /* Initialize curl globally */
    curl_global_init(CURL_GLOBAL_DEFAULT);

    /* Perform download with security controls */
    result = download_ftp_file(argv[1], argv[2], argv[3], safe_remote_file, safe_local_file);

    /* Securely clear password from memory */
    if (argv[3] != NULL) {
        secure_zero(argv[3], strlen(argv[3]));
    }

    /* Cleanup curl */
    curl_global_cleanup();

    return (result == 0) ? 0 : 1;
}
