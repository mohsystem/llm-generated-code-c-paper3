#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// Structure to hold downloaded data
struct MemoryStruct {
  char *memory;
  size_t size;
};

// Callback function for libcurl to write data to memory
static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if (ptr == NULL) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}


void retrieve_file(const char *file_name) {
    CURL *curl_handle;
    CURLcode res;
    struct MemoryStruct chunk;
    char full_url[256]; // Adjust size if needed


    chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */ 
    chunk.size = 0;    /* no data at this point */ 
    
    // Security: Basic extension check (improve this in real applications)
    const char *extension = strrchr(file_name, '.');
    if (extension != NULL) {
        if (strcmp(extension, ".exe") == 0 || strcmp(extension, ".sh") == 0 || strcmp(extension, ".bat") == 0) {
            fprintf(stderr, "Error: Downloading executables is not allowed.\n");
            free(chunk.memory);
            return;
        }
    }


    snprintf(full_url, sizeof(full_url), "http://example.com/%s", file_name);


    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();

    curl_easy_setopt(curl_handle, CURLOPT_URL, full_url);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    res = curl_easy_perform(curl_handle);

    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    } else {
      FILE *fp = fopen(file_name, "wb");
      if(fp == NULL) {
          fprintf(stderr, "Error opening file for writing.\n");
          curl_easy_cleanup(curl_handle);
          free(chunk.memory);
          return;
      }
      fwrite(chunk.memory, 1, chunk.size, fp);
      fclose(fp);
      printf("File downloaded successfully: %s\n", file_name);

    }



    curl_easy_cleanup(curl_handle);
    free(chunk.memory);
    curl_global_cleanup();
}

int main() {
    retrieve_file("test.txt");
    retrieve_file("image.jpg");
    retrieve_file("data.csv");
    retrieve_file("document.pdf");
    retrieve_file("malicious.exe"); // This will trigger the security check
    return 0;
}