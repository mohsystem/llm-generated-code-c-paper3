
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <ctype.h>

#define MAX_URL_LENGTH 2048
#define MAX_RESPONSE_SIZE (10 * 1024 * 1024)

typedef struct {
    char* data;
    size_t size;
    size_t capacity;
} Response;

// Security: Initialize response structure with NULL checks
Response* response_init(void) {
    Response* resp = (Response*)calloc(1, sizeof(Response));
    if (resp == NULL) {
        return NULL;
    }
    
    resp->capacity = 4096;
    resp->data = (char*)calloc(resp->capacity, sizeof(char));
    if (resp->data == NULL) {
        free(resp);
        return NULL;
    }
    
    resp->size = 0;
    return resp;
}

// Security: Free response memory safely
void response_free(Response* resp) {
    if (resp != NULL) {
        if (resp->data != NULL) {
            // Security: Clear sensitive data before freeing
            memset(resp->data, 0, resp->capacity);
            free(resp->data);
            resp->data = NULL;
        }
        free(resp);
    }
}

// Security: Safe write callback with bounds checking (Rules#6)
static size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t total_size = size * nmemb;
    Response* resp = (Response*)userp;
    
    // Security: Null pointer checks
    if (resp == NULL || contents == NULL) {
        return 0;
    }
    
    // Security: Prevent excessive memory usage
    if (resp->size + total_size > MAX_RESPONSE_SIZE) {
        return 0;
    }
    
    // Security: Grow buffer if needed with bounds check
    if (resp->size + total_size >= resp->capacity) {
        size_t new_capacity = resp->capacity * 2;
        if (new_capacity > MAX_RESPONSE_SIZE) {
            new_capacity = MAX_RESPONSE_SIZE;
        }
        
        char* new_data = (char*)realloc(resp->data, new_capacity);
        if (new_data == NULL) {
            return 0; // Memory allocation failed
        }
        
        resp->data = new_data;
        resp->capacity = new_capacity;
    }
    
    // Security: Safe memory copy with bounds check
    memcpy(resp->data + resp->size, contents, total_size);
    resp->size += total_size;
    resp->data[resp->size] = '\\0'; // Null terminate
    
    return total_size;
}

// Security: Validate URL format and scheme (Rules#5)
int is_valid_url(const char* url) {
    size_t len;
    size_t i;
    
    // Security: Null pointer check
    if (url == NULL) {
        return 0;
    }
    
    len = strlen(url);
    
    // Security: Validate length
    if (len == 0 || len > MAX_URL_LENGTH) {
        return 0;
    }
    
    // Security: Only allow HTTPS
    if (strncmp(url, "https://", 8) != 0) {
        return 0;
    }
    
    // Security: Check for valid printable characters
    for (i = 0; i < len; i++) {
        if (url[i] < 32 || url[i] > 126) {
            return 0;
        }
    }
    
    return 1;
}

// Security: Make HTTP request with all security measures
char* make_http_request(const char* url) {
    CURL* curl = NULL;
    CURLcode res;
    Response* response = NULL;
    char* result = NULL;
    
    // Security: Validate URL (Rules#5)
    if (!is_valid_url(url)) {
        result = (char*)calloc(64, sizeof(char));
        if (result != NULL) {
            snprintf(result, 63, "ERROR: Invalid URL. Only HTTPS URLs are allowed.");
        }
        return result;
    }
    
    curl = curl_easy_init();
    if (curl == NULL) {
        result = (char*)calloc(64, sizeof(char));
        if (result != NULL) {
            snprintf(result, 63, "ERROR: Failed to initialize CURL");
        }
        return result;
    }
    
    response = response_init();
    if (response == NULL) {
        curl_easy_cleanup(curl);
        result = (char*)calloc(64, sizeof(char));
        if (result != NULL) {
            snprintf(result, 63, "ERROR: Memory allocation failed");
        }
        return result;
    }
    
    // Security: Configure CURL with secure options
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
    
    // Security: Enable SSL/TLS certificate verification (Rules#3)
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L); // Rules#4: Hostname verification
    
    // Security: Set timeouts
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
    
    // Security: Limit redirects
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 5L);
    
    // Security: Only HTTPS protocol
    curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTPS);
    curl_easy_setopt(curl, CURLOPT_REDIR_PROTOCOLS, CURLPROTO_HTTPS);
    
    res = curl_easy_perform(curl);
    
    if (res != CURLE_OK) {
        const char* error_msg = curl_easy_strerror(res);
        size_t error_len = strlen(error_msg);
        result = (char*)calloc(error_len + 32, sizeof(char));
        if (result != NULL) {
            snprintf(result, error_len + 31, "ERROR: Request failed: %s", error_msg);
        }
    } else {
        // Security: Copy response with bounds check
        result = (char*)calloc(response->size + 1, sizeof(char));
        if (result != NULL) {
            memcpy(result, response->data, response->size);
            result[response->size] = '\\0';
        }
    }
    
    curl_easy_cleanup(curl);
    response_free(response);
    
    return result;
}

int main(void) {
    const char* test_urls[] = {
        "https://www.example.com",
        "https://httpbin.org/get",
        "http://insecure.com",
        "https://invalid..url",
        ""
    };
    int i;
    
    printf("=== HTTP Request Program ===\\n\\n");
    
    for (i = 0; i < 5; i++) {
        char* result = NULL;
        printf("Test %d: %s\\n", i + 1, test_urls[i]);
        
        result = make_http_request(test_urls[i]);
        
        if (result != NULL) {
            // Security: Don't print entire response
            if (strncmp(result, "ERROR:", 6) == 0) {
                printf("%s\\n", result);
            } else {
                printf("SUCCESS: Received %zu bytes\\n", strlen(result));
            }
            
            // Security: Clear and free memory
            memset(result, 0, strlen(result));
            free(result);
            result = NULL;
        } else {
            printf("ERROR: Memory allocation failed\\n");
        }
        
        printf("---\\n\\n");
    }
    
    return 0;
}
