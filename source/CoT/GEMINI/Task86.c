#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <curl/curl.h>

// Link with the URL Moniker library for URLDownloadToFile

/**
 * WARNING: This function downloads and executes a file from the internet.
 * This is an extremely dangerous operation and can expose your system to
 * malware and other security risks. Only use this with URLs from sources
 * you completely trust. The downloaded executable will have the same
 * permissions as the user running this program.
 *
 * This function is Windows-specific.
 *
 * @param url The URL of the EXE file to download and execute.
 * @return true if the process was started successfully, false otherwise.
 */
bool downloadAndExecute(const char* url) {
    char finalExePath[PATH_MAX];
    bool success = false;

    // 1. Create a secure temporary file path
    char tempTemplate[] = "/tmp/DEXXXXXXX";
    int fd = mkstemp(tempTemplate);
    if (fd == -1) {
        fprintf(stderr, "Error creating temp file name: %s\n", strerror(errno));
        return false;
    }
    close(fd);

    // Rename the file to have a .exe extension
    snprintf(finalExePath, sizeof(finalExePath), "%s.exe", tempTemplate);
    if (rename(tempTemplate, finalExePath) != 0) {
        fprintf(stderr, "Error renaming temp file: %s\n", strerror(errno));
        unlink(tempTemplate); // Cleanup original temp file
        return false;
    }

    // 2. Download the file
    printf("Downloading from %s to %s\n", url, finalExePath);
    CURL* curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Error initializing curl\n");
        goto cleanup;
    }
    FILE* out = fopen(finalExePath, "wb");
    if (!out) {
        fprintf(stderr, "Error opening temp file for writing: %s\n", strerror(errno));
        curl_easy_cleanup(curl);
        goto cleanup;
    }
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, out);
    CURLcode res = curl_easy_perform(curl);
    fclose(out);
    curl_easy_cleanup(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Error downloading file. CURL: %s\n", curl_easy_strerror(res));
        goto cleanup; // Go to cleanup section
    }

    // 3. Execute the downloaded file
    printf("Executing %s\n", finalExePath);
    // Using CreateProcess is secure as it does not involve the shell.
    if (chmod(finalExePath, 0700) != 0) {
        fprintf(stderr, "chmod failed: %s\n", strerror(errno));
        goto cleanup;
    }
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork failed: %s\n", strerror(errno));
        goto cleanup;
    } else if (pid == 0) {
        execl(finalExePath, finalExePath, (char*)NULL);
        fprintf(stderr, "exec failed: %s\n", strerror(errno));
        _exit(127);
    }
    printf("Process started successfully with PID: %ld\n", (long)pid);
    success = true;

cleanup:
    // 4. Cleanup: Delete the temporary file
    if (unlink(finalExePath) == 0) {
        printf("Cleaned up temporary file: %s\n", finalExePath);
    } else {
        // May fail if the process is still running, but we should try
        fprintf(stderr, "Failed to delete temporary file: %s (Error: %s)\n", finalExePath, strerror(errno));
    }

    return success;
}

int main(int argc, char* argv[]) {
    printf("--- Running Test Cases ---\n");

    // Test Case 1: A well-known, safe 64-bit executable (PuTTY)
    printf("\n--- Test Case 1: Valid 64-bit EXE (PuTTY) ---\n");
    downloadAndExecute("https://the.earth.li/~sgtatham/putty/latest/w64/putty.exe");

    // Test Case 2: A well-known, safe portable executable (Process Explorer)
    printf("\n--- Test Case 2: Valid portable EXE (Process Explorer) ---\n");
    downloadAndExecute("https://live.sysinternals.com/procexp.exe");

    // Test Case 3: An invalid URL that will fail to download
    printf("\n--- Test Case 3: Invalid URL ---\n");
    downloadAndExecute("https://this-is-a-fake-url-12345.com/nonexistent.exe");

    // Test Case 4: A valid URL to a non-executable file
    printf("\n--- Test Case 4: Valid URL, but not an EXE ---\n");
    downloadAndExecute("https://www.google.com/images/branding/googlelogo/1x/googlelogo_color_272x92dp.png");

    // Test Case 5: A well-known, safe 32-bit executable (PuTTY)
    printf("\n--- Test Case 5: Valid 32-bit EXE (PuTTY) ---\n");
    downloadAndExecute("https://the.earth.li/~sgtatham/putty/latest/w32/putty.exe");

    return 0;
}
