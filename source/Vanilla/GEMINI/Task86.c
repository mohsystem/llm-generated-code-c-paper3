// Build (Linux):
//   sudo apt-get install -y libcurl4-openssl-dev
//   gcc download_run_linux.c -o download_run_linux -lcurl
//
// WARNING: Downloading and executing files from the internet can be extremely dangerous.
// Only use trusted URLs. This version targets Linux and executes ELF binaries (not Windows .exe).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <curl/curl.h>

/**
 * Downloads an executable file from a URL and runs it.
 * This function is specific to the Linux operating system.
 * @param url The URL of the executable file to download.
 * @param fileName The local filename to save the executable as.
 */
void downloadAndExecute(const char* url, const char* fileName) {
    // Step 1: Download the file using libcurl
    printf("Downloading %s to %s...\n", url, fileName);

    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to init libcurl\n");
        return;
    }

    FILE *fp = fopen(fileName, "wb");
    if (!fp) {
        fprintf(stderr, "Failed to open output file '%s': %s\n", fileName, strerror(errno));
        curl_easy_cleanup(curl);
        return;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    // Fail on HTTP errors (4xx/5xx)
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

    CURLcode res = curl_easy_perform(curl);
    fclose(fp);
    if (res != CURLE_OK) {
        fprintf(stderr, "Failed to download file: %s\n", curl_easy_strerror(res));
        // Remove partial file if any
        unlink(fileName);
        curl_easy_cleanup(curl);
        return;
    }

    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    curl_easy_cleanup(curl);

    printf("Download complete (HTTP %ld).\n", http_code);

    // Step 2: Mark the file executable
    if (chmod(fileName, 0700) != 0) {
        fprintf(stderr, "chmod failed on '%s': %s\n", fileName, strerror(errno));
        return;
    }

    // Step 3: Execute the downloaded file (direct exec, no shell)
    printf("Executing %s...\n", fileName);
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork failed: %s\n", strerror(errno));
        return;
    } else if (pid == 0) {
        // Child: exec the binary
        execl(fileName, fileName, (char*)NULL);
        // If we reach here, exec failed
        fprintf(stderr, "exec failed for '%s': %s\n", fileName, strerror(errno));
        _exit(127);
    }

    // Parent: wait for child
    int status = 0;
    if (waitpid(pid, &status, 0) < 0) {
        fprintf(stderr, "waitpid failed: %s\n", strerror(errno));
        return;
    }

    if (WIFEXITED(status)) {
        printf("'%s' finished with exit code: %d\n", fileName, WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("'%s' terminated by signal: %d\n", fileName, WTERMSIG(status));
    } else {
        printf("'%s' ended with unknown status: 0x%x\n", fileName, status);
    }
}

int main() {
    // NOTE: The original example used a Windows .exe URL (PuTTY for Windows),
    // which will NOT run on Linux. Replace 'fileUrl' with a Linux ELF binary URL
    // if you want actual execution. The function itself works on Linux.
    const char* fileUrl = "https://the.earth.li/~sgtatham/putty/latest/w64/putty.exe";

    printf("--- Starting 5 Test Cases ---\n");

    printf("\n--- Test Case 1 ---\n");
    downloadAndExecute(fileUrl, "putty_c_1");

    printf("\n--- Test Case 2 ---\n");
    downloadAndExecute(fileUrl, "putty_c_2");

    printf("\n--- Test Case 3 ---\n");
    downloadAndExecute(fileUrl, "putty_c_3");

    printf("\n--- Test Case 4 ---\n");
    downloadAndExecute(fileUrl, "putty_c_4");

    printf("\n--- Test Case 5 ---\n");
    downloadAndExecute(fileUrl, "putty_c_5");

    printf("\n--- All tests completed ---\n");
    return 0;
}
