#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#define MKDIR(path) _mkdir(path)
#define PATH_SEP '\\'
#define POPEN _popen
#define PCLOSE _pclose
#else
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define MKDIR(path) mkdir(path, 0700)
#define PATH_SEP '/'
#define POPEN popen
#define PCLOSE pclose
#endif

static void safe_strcpy(char* dst, size_t dstsz, const char* src) {
    if (!dst || dstsz == 0) return;
    if (!src) { dst[0] = '\0'; return; }
    strncpy(dst, src, dstsz - 1);
    dst[dstsz - 1] = '\0';
}

static void safe_strcat(char* dst, size_t dstsz, const char* src) {
    if (!dst || dstsz == 0 || !src) return;
    size_t l = strlen(dst);
    if (l >= dstsz - 1) return;
    strncat(dst, src, dstsz - l - 1);
}

static int safe_chars(const char* s) {
    if (!s) return 0;
    size_t len = strlen(s);
    if (len == 0 || len > 255) return 0;
    for (size_t i = 0; i < len; ++i) {
        char c = s[i];
        if (!(isalnum((unsigned char)c) || c == '.' || c == '_' || c == '-' || c == '/' || c == '\\')) {
            return 0;
        }
    }
    return 1;
}

static char* str_dup(const char* s) {
    size_t n = strlen(s) + 1;
    char* p = (char*)malloc(n);
    if (p) memcpy(p, s, n);
    return p;
}

// Normalize a relative path: remove "." and ".."
static char* normalize_relative(const char* rel) {
    char* temp = str_dup(rel);
    if (!temp) return NULL;

    for (char* t = temp; *t; ++t) {
        if (*t == '/' || *t == '\\') *t = PATH_SEP;
    }

    const size_t max_parts = 512;
    char* parts[512];
    size_t count = 0;

#if defined(_WIN32)
    char* saveptr = NULL;
    char delim[2] = { PATH_SEP, '\0' };
    char* token = strtok_s(temp, delim, &saveptr);
#else
    char* saveptr = NULL;
    char delim[2] = { PATH_SEP, '\0' };
    char* token = strtok_r(temp, delim, &saveptr);
#endif

    while (token) {
        if (strcmp(token, ".") == 0) {
            // skip
        } else if (strcmp(token, "..") == 0) {
            if (count > 0) count--;
            else { free(temp); return NULL; }
        } else {
            if (count >= max_parts) { free(temp); return NULL; }
            parts[count++] = token;
        }
#if defined(_WIN32)
        token = strtok_s(NULL, delim, &saveptr);
#else
        token = strtok_r(NULL, delim, &saveptr);
#endif
    }

    size_t total = 1;
    for (size_t i = 0; i < count; ++i) total += strlen(parts[i]) + 1;

    char* out = (char*)malloc(total > 1 ? total : 2);
    if (!out) { free(temp); return NULL; }
    out[0] = '\0';

    for (size_t i = 0; i < count; ++i) {
        if (i > 0) {
            size_t l = strlen(out);
            out[l] = PATH_SEP;
            out[l + 1] = '\0';
        }
        safe_strcat(out, total, parts[i]);
    }
    if (count == 0) {
        safe_strcpy(out, total, ".");
    }

    free(temp);
    return out;
}

static int is_prefix_path(const char* base, const char* path) {
    size_t bl = strlen(base);
    if (strncmp(base, path, bl) != 0) return 0;
    if (path[bl] == '\0') return 1;
    if (path[bl] == '/' || path[bl] == '\\') return 1;
    return 0;
}

static int path_exists_regular_no_symlink(const char* full) {
#ifdef _WIN32
    char buf[4096];
    safe_strcpy(buf, sizeof(buf), full);
    for (char* p = buf; *p; ++p) if (*p == '/') *p = '\\';

    DWORD attr = GetFileAttributesA(buf);
    if (attr == INVALID_FILE_ATTRIBUTES) return 0;
    if (attr & FILE_ATTRIBUTE_REPARSE_POINT) return 0;
    if (attr & FILE_ATTRIBUTE_DIRECTORY) return 0;
    return 1;
#else
    struct stat st;
    if (lstat(full, &st) != 0) return 0;
    if (S_ISLNK(st.st_mode)) return 0;
    if (!S_ISREG(st.st_mode)) return 0;
    return 1;
#endif
}

static int has_symlink_in_path(const char* path) {
#ifdef _WIN32
    char buf[4096];
    safe_strcpy(buf, sizeof(buf), path);
    for (char* p = buf; *p; ++p) if (*p == '/') *p = '\\';

    char acc[4096] = {0};
    size_t len = strlen(buf);
    for (size_t i = 0; i < len; ++i) {
        acc[i] = buf[i];
        acc[i + 1] = '\0';
        if (buf[i] == '\\') {
            DWORD attr = GetFileAttributesA(acc);
            if (attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_REPARSE_POINT)) {
                return 1;
            }
        }
    }
    return 0;
#else
    struct stat st;
    char tmp[4096];
    safe_strcpy(tmp, sizeof(tmp), path);
    size_t n = strlen(tmp);
    for (size_t i = 1; i < n; ++i) {
        if (tmp[i] == PATH_SEP) {
            char saved = tmp[i];
            tmp[i] = '\0';
            if (lstat(tmp, &st) == 0) {
                if (S_ISLNK(st.st_mode)) return 1;
            }
            tmp[i] = saved;
        }
    }
    return 0;
#endif
}

static char* run_command_show(const char* full) {
#ifdef _WIN32
    char cmd[4096];
    snprintf(cmd, sizeof(cmd), "more \"%s\"", full);
#else
    char cmd[4096];
    snprintf(cmd, sizeof(cmd), "cat \"%s\"", full);
#endif
    FILE* pipe = POPEN(cmd, "r");
    if (!pipe) {
        return str_dup("ERROR: Failed to start command");
    }
    size_t cap = 4096, len = 0;
    char* out = (char*)malloc(cap);
    if (!out) { PCLOSE(pipe); return str_dup("ERROR: Memory allocation"); }
    out[0] = '\0';
    char buf[1024];
    while (fgets(buf, sizeof(buf), pipe)) {
        size_t bl = strlen(buf);
        if (len + bl + 1 > cap) {
            size_t ncap = (cap * 2 > len + bl + 1) ? cap * 2 : len + bl + 1;
            char* tmp = (char*)realloc(out, ncap);
            if (!tmp) { free(out); PCLOSE(pipe); return str_dup("ERROR: Memory allocation"); }
            out = tmp;
            cap = ncap;
        }
        memcpy(out + len, buf, bl);
        len += bl;
        out[len] = '\0';
    }
    int rc = PCLOSE(pipe);
    if (rc != 0 && len == 0) {
        free(out);
        return str_dup("ERROR: Command failed");
    }
    return out;
}

char* display_file_using_command(const char* base_dir, const char* user_input) {
    if (!user_input) {
        return str_dup("ERROR: Invalid input");
    }
    if (!safe_chars(user_input)) {
        return str_dup("ERROR: Invalid filename: characters or length");
    }

    MKDIR(base_dir);

    char* norm_rel = normalize_relative(user_input);
    if (!norm_rel) {
        return str_dup("ERROR: Path traversal detected or normalization failed");
    }

    char full[4096];
    if (snprintf(full, sizeof(full), "%s%c%s", base_dir, PATH_SEP, norm_rel) >= (int)sizeof(full)) {
        free(norm_rel);
        return str_dup("ERROR: Path too long");
    }
    free(norm_rel);

    char full_norm[4096];
    safe_strcpy(full_norm, sizeof(full_norm), full);
    for (char* p = full_norm; *p; ++p) {
        if (*p == '/' || *p == '\\') *p = PATH_SEP;
    }

    char base_norm[4096];
    safe_strcpy(base_norm, sizeof(base_norm), base_dir);
    for (char* p = base_norm; *p; ++p) {
        if (*p == '/' || *p == '\\') *p = PATH_SEP;
    }
    if (!is_prefix_path(base_norm, full_norm)) {
        return str_dup("ERROR: Path traversal detected");
    }

    if (has_symlink_in_path(full_norm)) {
        return str_dup("ERROR: Symlink not allowed in path");
    }

    if (!path_exists_regular_no_symlink(full_norm)) {
        return str_dup("ERROR: File does not exist or is not a regular file");
    }

    return run_command_show(full_norm);
}

static int write_file(const char* path, const char* content) {
    FILE* f = fopen(path, "wb");
    if (!f) return -1;
    size_t n = fwrite(content, 1, strlen(content), f);
    fclose(f);
    return (n == strlen(content)) ? 0 : -1;
}

int main(void) {
    const char* base = "safe_base_dir_task39_c";
    MKDIR(base);

    char path1[512], subdir[512], path2[512], emptydir[512];
    snprintf(path1, sizeof(path1), "%s%c%s", base, PATH_SEP, "file1.txt");
    snprintf(subdir, sizeof(subdir), "%s%c%s", base, PATH_SEP, "subdir");
    MKDIR(subdir);
    snprintf(path2, sizeof(path2), "%s%c%s%c%s", base, PATH_SEP, "subdir", PATH_SEP, "file2.txt");
    snprintf(emptydir, sizeof(emptydir), "%s%c%s", base, PATH_SEP, "emptydir");
    MKDIR(emptydir);

    write_file(path1, "Hello from C file1\nLine2\n");
    write_file(path2, "Hello from C subdir file2\n");

    const char* tests[5] = {
        "file1.txt",
        "subdir/file2.txt",
        "../outside.txt",
        "nonexistent.txt",
        "subdir"
    };

    for (int i = 0; i < 5; ++i) {
        printf("=== Test %d: %s ===\n", i + 1, tests[i]);
        char* out = display_file_using_command(base, tests[i]);
        if (out) {
            fputs(out, stdout);
            free(out);
        } else {
            printf("ERROR: Unknown\n");
        }
    }
    return 0;
}
