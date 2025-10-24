
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <ctype.h>

#include "../../../../../../../../usr/include/stdint.h"

#define MAX_FILENAME_LEN 255
#define MAX_URL_LEN 512
#define MAX_RESPONSE_SIZE (10 * 1024 * 1024) /* 10 MB limit */
#define BASE_URL "https://example.com/files/"

/* Structure to hold response data */
typedef struct {
    char *data;
    size_t size;
    size_t capacity;
} ResponseBuffer;

/* Secure memory clearing function that compiler cannot optimize away */
static void secure_zero(void *ptr, size_t len) {
    if (ptr == NULL) return;
    volatile unsigned char *p = (volatile unsigned char *)ptr;
    while (len--) {
        *p++ = 0;
    }
}

/* Initialize response buffer */
static int init_response_buffer(ResponseBuffer *buf) {
    if (buf == NULL) return 0;
    
    buf->capacity = 4096;
    buf->data = (char *)calloc(1, buf->capacity);
    if (buf->data == NULL) {
        return 0;
    }
    buf->size = 0;
    return 1;
}

/* Free response buffer with secure clearing */
static void free_response_buffer(ResponseBuffer *buf) {
    if (buf == NULL) return;
    if (buf->data != NULL) {
        secure_zero(buf->data, buf->capacity);
        free(buf->data);
        buf->data = NULL;
    }
    buf->size = 0;
    buf->capacity = 0;
}

/* Callback for curl write operation with bounds checking and growth limit */
static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize;
    ResponseBuffer *buf = (ResponseBuffer *)userp;
    
    if (buf == NULL || contents == NULL) return 0;
    
    /* Check for integer overflow in multiplication */
    if (size > 0 && nmemb > SIZE_MAX / size) {
        return 0;
    }
    realsize = size * nmemb;
    
    /* Check for integer overflow in addition */
    if (buf->size > SIZE_MAX - realsize) {
        return 0;
    }
    
    /* Enforce maximum response size to prevent excessive memory usage */
    if (buf->size + realsize > MAX_RESPONSE_SIZE) {
        return 0;
    }
    
    /* Grow buffer if needed */
    if (buf->size + realsize + 1 > buf->capacity) {
        size_t new_capacity = buf->capacity * 2;
        
        /* Ensure new capacity is large enough */
        while (new_capacity < buf->size + realsize + 1) {
            if (new_capacity > SIZE_MAX / 2) {
                return 0;
            }
            new_capacity *= 2;
        }
        
        /* Check against maximum allowed size */
        if (new_capacity > MAX_RESPONSE_SIZE) {
            new_capacity = MAX_RESPONSE_SIZE;
            if (buf->size + realsize + 1 > new_capacity) {
                return 0;
            }
        }
        
        char *new_data = (char *)realloc(buf->data, new_capacity);
        if (new_data == NULL) {
            return 0;
        }
        
        buf->data = new_data;
        buf->capacity = new_capacity;
    }
    
    /* Copy data with bounds checking */
    memcpy(buf->data + buf->size, contents, realsize);
    buf->size += realsize;
    buf->data[buf->size] = '\0'; /* Ensure null termination */
    
    return realsize;
}
/* Validate filename to prevent path traversal attacks */
static int validate_filename(const char *filename) {
    size_t len;
    size_t i;

    if (filename == NULL) return 0;

    len = strlen(filename);

    /* Check length bounds */
    if (len == 0 || len > MAX_FILENAME_LEN) {
        return 0;
    }

    /* Reject paths with traversal patterns */
    if (strstr(filename, "..") != NULL) {
        return 0;
    }
    if (strstr(filename, "./") != NULL || strstr(filename, "/.") != NULL) {
        return 0;
    }
    if (filename[0] == '/' || filename[0] == '\\') {
        return 0;
    }

    /* Check for path separators and other dangerous characters */
    for (i = 0; i < len; i++) {
        char c = filename[i];
        if (c == '/' || c == '\\' || c == ':' || c == '*' ||
            c == '?' || c == '"' || c == '<' || c == '>' || c == '|') {
            return 0;
        }
        /* Reject control characters */
        if (iscntrl((unsigned char)c)) {
            return 0;
        }
    }

    return 1;
}

/* URL encode a string to prevent injection attacks */
static char *url_encode(const char *str) {
    size_t len;
    size_t i;
    size_t encoded_len;
    char *encoded;
    size_t pos;

    if (str == NULL) return NULL;

    len = strlen(str);

    /* Check for integer overflow: each char can expand to %XX (3 bytes) */
    if (len > SIZE_MAX / 3) {
        return NULL;
    }

    encoded_len = len * 3 + 1;
    encoded = (char *)calloc(1, encoded_len);
    if (encoded == NULL) {
        return NULL;
    }

    pos = 0;
    for (i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];

        /* Check bounds before writing */
        if (pos + 4 > encoded_len) {
            secure_zero(encoded, encoded_len);
            free(encoded);
            return NULL;
        }

        /* Encode special characters */
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            encoded[pos++] = c;
        } else {
            int written = snprintf(encoded + pos, encoded_len - pos, "%%%02X", c);
            if (written < 0 || written >= (int)(encoded_len - pos)) {
                secure_zero(encoded, encoded_len);
                free(encoded);
                return NULL;
            }
            pos += written;
        }
    }

    encoded[pos] = '\0';
    return encoded;
}

/* Retrieve file from server using HTTPS with full security settings */
static int retrieve_file(const char *filename, ResponseBuffer *response) {
    CURL *curl = NULL;
    CURLcode res;
    char url[MAX_URL_LEN];
    char *encoded_filename = NULL;
    int result = 0;

    if (filename == NULL || response == NULL) {
        return 0;
    }

    /* Validate filename to prevent path traversal */
    if (!validate_filename(filename)) {
        fprintf(stderr, "Error: Invalid filename\n");
        return 0;
    }

    /* URL encode the filename to prevent injection */
    encoded_filename = url_encode(filename);
    if (encoded_filename == NULL) {
        fprintf(stderr, "Error: Failed to encode filename\n");
        return 0;
    }

    /* Build URL with bounds checking */
    if (snprintf(url, sizeof(url), "%s%s", BASE_URL, encoded_filename) >= (int)sizeof(url)) {
        fprintf(stderr, "Error: URL too long\n");
        secure_zero(encoded_filename, strlen(encoded_filename));
        free(encoded_filename);
        return 0;
    }

    /* Clean up encoded filename */
    secure_zero(encoded_filename, strlen(encoded_filename));
    free(encoded_filename);
    encoded_filename = NULL;

    curl = curl_easy_init();
    if (curl == NULL) {
        fprintf(stderr, "Error: Failed to initialize curl\n");
        return 0;
    }

    /* Set URL */
    res = curl_easy_setopt(curl, CURLOPT_URL, url);
    if (res != CURLE_OK) goto cleanup;

    /* Restrict to HTTPS only */
    res = curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTPS);
    if (res != CURLE_OK) goto cleanup;

    /* Enable SSL certificate verification */
    res = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    if (res != CURLE_OK) goto cleanup;

    /* Enable hostname verification */
    res = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
    if (res != CURLE_OK) goto cleanup;

    /* Set minimum TLS version to 1.2 */
    res = curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
    if (res != CURLE_OK) goto cleanup;

    /* Set timeouts */
    res = curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 30L);
    if (res != CURLE_OK) goto cleanup;

    res = curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60L);
    if (res != CURLE_OK) goto cleanup;

    /* Limit redirects */
    res = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    if (res != CURLE_OK) goto cleanup;

    res = curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 3L);
    if (res != CURLE_OK) goto cleanup;

    /* Set write callback and buffer */
    res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    if (res != CURLE_OK) goto cleanup;

    res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)response);
    if (res != CURLE_OK) goto cleanup;

    /* Perform the request */
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Error: Request failed\n");
        goto cleanup;
    }

    /* Check HTTP response code */
    long response_code = 0;
    res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    if (res != CURLE_OK || response_code != 200) {
        fprintf(stderr, "Error: Invalid response\n");
        goto cleanup;
    }

    result = 1;

cleanup:
    if (curl != NULL) {
        curl_easy_cleanup(curl);
    }

    return result;
}

int main(void) {
    const char *test_files[] = {
        "document.txt",
        "data.json",
        "report.pdf",
        "image.png",
        "config.xml"
    };
    int i;
    CURLcode res;

    /* Initialize curl globally */
    res = curl_global_init(CURL_GLOBAL_DEFAULT);
    if (res != CURLE_OK) {
        fprintf(stderr, "Error: Failed to initialize curl library\n");
        return EXIT_FAILURE;
    }

    printf("File Retrieval System - Test Cases\n");
    printf("===================================\n\n");

    /* Test with 5 different filenames */
    for (i = 0; i < 5; i++) {
        ResponseBuffer response;

        printf("Test %d: Retrieving file '%s'\n", i + 1, test_files[i]);

        /* Initialize response buffer */
        if (!init_response_buffer(&response)) {
            fprintf(stderr, "Error: Failed to initialize buffer\n");
            continue;
        }

        /* Retrieve file */
        if (retrieve_file(test_files[i], &response)) {
            printf("Success: Retrieved %zu bytes\n", response.size);

            /* Display first 100 bytes or less */
            size_t preview_len = response.size < 100 ? response.size : 100;
            if (preview_len > 0) {
                printf("Preview: ");
                fwrite(response.data, 1, preview_len, stdout);
                if (response.size > 100) {
                    printf("...");
                }
                printf("\n");
            }
        } else {
            printf("Failed to retrieve file\n");
        }

        /* Clean up response buffer */
        free_response_buffer(&response);
        printf("\n");
    }

    /* Test path traversal attempt (should fail) */
    printf("Test 6: Security test - path traversal attempt\n");
    ResponseBuffer response;
    if (!init_response_buffer(&response)) {
        fprintf(stderr, "Error: Failed to initialize buffer\n");
    } else {
        if (retrieve_file("../../../etc/passwd", &response)) {
            printf("SECURITY FAILURE: Path traversal was not blocked\n");
        } else {
            printf("Success: Path traversal attack blocked\n");
        }
        free_response_buffer(&response);
    }

    /* Cleanup curl globally */
    curl_global_cleanup();

    return EXIT_SUCCESS;
}
