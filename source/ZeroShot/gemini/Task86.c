#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#endif


// Callback function for cURL to write data to a file
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void download_and_execute(const char *url) {
    CURL *curl;
    FILE *fp;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        fp = fopen("downloaded.exe", "wb");
        if (fp) {
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            fclose(fp);


            if (res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                return;
            }


             // Execute downloaded file (highly insecure - sanitize and validate in real applications).
#ifdef _WIN32
            STARTUPINFOA si;
            PROCESS_INFORMATION pi;
            ZeroMemory(&si, sizeof(si));
            si.cb = sizeof(si);
            ZeroMemory(&pi, sizeof(pi));

             if (!CreateProcessA("downloaded.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
                fprintf(stderr, "CreateProcess failed\n");
                return;
            }
            // Wait for the process to finish (optional)
            WaitForSingleObject(pi.hProcess, INFINITE);
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);

#else // POSIX systems (Linux, macOS, etc.)
            pid_t pid = fork();
            if (pid == 0) { // Child process
                execl("./downloaded.exe", "downloaded.exe", (char *)NULL);
                perror("execl failed");
                _exit(1); // Exit child if execl fails
            } else if (pid > 0) { // Parent process
                int status;
                waitpid(pid, &status, 0); // Wait for child to finish
                if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                    fprintf(stderr, "Child process exited with error: %d\n", WEXITSTATUS(status));
                }
            } else { // fork failed
                perror("fork failed");
            }

#endif
        } else {
             perror("fopen failed");
        }
    } else {
        fprintf(stderr, "curl_easy_init() failed\n");
    }
}



int main() {
     // Example URLs (replace these with valid URLs for testing)
    const char *urls[] = {
        "https://example.com/file1.exe",
        "https://example.com/file2.exe",
        "https://example.com/file3.exe",
        "https://example.com/file4.exe",
        "https://example.com/file5.exe"
    };
    int num_urls = sizeof(urls) / sizeof(urls[0]);

    curl_global_init(CURL_GLOBAL_ALL); // Initialize libcurl

    for (int i = 0; i < num_urls; i++) {
        download_and_execute(urls[i]);
    }

    curl_global_cleanup();  // Cleanup libcurl

    return 0;
}