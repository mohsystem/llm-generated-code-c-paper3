// Build on Linux:
//   sudo apt-get install -y libcurl4-openssl-dev
//   gcc download_and_execute_linux.c -o download_and_execute_linux -lcurl
//
// WARNING: Downloading and executing binaries from the internet is risky.
// Only use trusted URLs. This Linux version expects an ELF binary (not a .exe).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <curl/curl.h>

static int ensure_dir_exists(const char* dir) {
    struct stat st;
    if (stat(dir, &st) == 0) {
        return S_ISDIR(st.st_mode) ? 0 : -1;
    }
    if (mkdir(dir, 0755) == 0) return 0;
    return (errno == EEXIST) ? 0 : -1;
}

static const char* pick_tmpdir(void) {
    const char* t = getenv("TMPDIR");
    if (t && *t) return t;
    return "/tmp";
}

// Returns process exit code, or negative value on error:
// -1 dir error, -2 download error, -3 chmod error, -4 fork error
int download_and_execute(const char* url, const char* destDirectory) {
    if (!url || !*url) return -2;

    char dirBuffer[PATH_MAX];
    if (destDirectory && *destDirectory) {
        if (strlen(destDirectory) >= sizeof(dirBuffer)) return -1;
        strcpy(dirBuffer, destDirectory);
    } else {
        const char* tmp = pick_tmpdir();
        if (strlen(tmp) >= sizeof(dirBuffer)) return -1;
        strcpy(dirBuffer, tmp);
    }

    if (ensure_dir_exists(dirBuffer) != 0) return -1;

    // Derive a filename; fallback to "downloaded_program"
    const char* last_slash = strrchr(url, '/');
    const char* fname = (last_slash && last_slash[1]) ? last_slash + 1 : "downloaded_program";
    if (strlen(fname) == 0) fname = "downloaded_program";

    // Compose target path; add a timestamp to avoid clashes
    char targetPath[PATH_MAX];
    snprintf(targetPath, sizeof(targetPath), "%s/%s_%ld", dirBuffer, "downloaded_program", (long)time(NULL));

    // If URL filename looks usable (and not too long), use it instead
    if (strlen(fname) < 200 && strchr(fname, '/') == NULL) {
        snprintf(targetPath, sizeof(targetPath), "%s/%s", dirBuffer, fname);
    }

    // Download using libcurl
    CURL* curl = curl_easy_init();
    if (!curl) return -2;

    FILE* fp = fopen(targetPath, "wb");
    if (!fp) {
        curl_easy_cleanup(curl);
        return -2;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
    CURLcode res = curl_easy_perform(curl);
    fclose(fp);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        unlink(targetPath); // remove partial
        fprintf(stderr, "Download failed: %s\n", curl_easy_strerror(res));
        return -2;
    }

    // Make it executable
    if (chmod(targetPath, 0700) != 0) {
        fprintf(stderr, "chmod failed on '%s': %s\n", targetPath, strerror(errno));
        unlink(targetPath);
        return -3;
    }

    // Execute (no shell)
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork failed: %s\n", strerror(errno));
        return -4;
    }
    if (pid == 0) {
        execl(targetPath, targetPath, (char*)NULL);
        // If exec fails:
        fprintf(stderr, "exec failed for '%s': %s\n", targetPath, strerror(errno));
        _exit(127);
    }

    int status = 0;
    if (waitpid(pid, &status, 0) < 0) {
        fprintf(stderr, "waitpid failed: %s\n", strerror(errno));
        return -4;
    }

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        // Encode signal as a negative value distinct from our error codes
        return -100 - WTERMSIG(status);
    }
    return -4;
}

int main(void) {
    // Replace with a Linux ELF binary URL if you want it to actually run.
    // These are placeholders and likely won't be ELF binaries.
    const char* tests[5] = {
        "https://example.com/program1",      // expect failure unless ELF
        "https://example.com/program2",
        "https://example.org/tools/setup",
        "https://example.net/app/latest",
        "https://example.com/download/myapp"
    };

    for (int i = 0; i < 5; ++i) {
        int rc = download_and_execute(tests[i], NULL);
        printf("URL: %s -> Exit Code: %d\n", tests[i], rc);
    }
    return 0;
}
