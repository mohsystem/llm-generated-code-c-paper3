#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <dirent.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#define DEFAULT_MAX_BYTES (10 * 1024 * 1024) /* 10MB */

static int is_symlink_nofollow(const char *path) {
    struct stat st;
    if (lstat(path, &st) != 0) return 0;
    return S_ISLNK(st.st_mode);
}

static int is_directory_nofollow(const char *path) {
    struct stat st;
    if (lstat(path, &st) != 0) return 0;
    return S_ISDIR(st.st_mode);
}

static int is_regular_nofollow(const char *path) {
    struct stat st;
    if (lstat(path, &st) != 0) return 0;
    return S_ISREG(st.st_mode);
}

/* Join base + requested relative path and normalize (handling . and ..) */
static int join_and_normalize(const char *base_abs, const char *req, char *out, size_t outsz) {
    if (!base_abs || !req || !out) return -1;
    if (strlen(base_abs) >= outsz) return -1;
    /* Ensure base_abs is absolute */
    if (base_abs[0] != '/') return -1;

    /* Start with base_abs */
    char temp[PATH_MAX];
    size_t len = 0;
    int need_slash = 0;
    /* Copy base_abs into temp */
    strncpy(temp, base_abs, sizeof(temp) - 1);
    temp[sizeof(temp) - 1] = '\0';
    len = strlen(temp);
    if (len == 0) return -1;
    /* Ensure no trailing slash except root */
    if (len > 1 && temp[len - 1] == '/') {
        temp[len - 1] = '\0';
        len--;
    }

    /* Process req */
    if (req[0] == '/') return -1; /* absolute not allowed */

    char buf[PATH_MAX];
    strncpy(buf, req, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';

    char *saveptr = NULL;
    char *token = strtok_r(buf, "/", &saveptr);
    char stack[PATH_MAX][NAME_MAX + 1];
    int sp = 0;

    while (token) {
        if (strcmp(token, ".") == 0 || strcmp(token, "") == 0) {
            /* ignore */
        } else if (strcmp(token, "..") == 0) {
            if (sp > 0) sp--;
        } else {
            if (strlen(token) > NAME_MAX) return -1;
            strncpy(stack[sp], token, NAME_MAX);
            stack[sp][NAME_MAX] = '\0';
            sp++;
        }
        token = strtok_r(NULL, "/", &saveptr);
    }

    /* Build output */
    size_t pos = 0;
    int written = snprintf(out, outsz, "%s", temp);
    if (written < 0 || (size_t)written >= outsz) return -1;
    pos = (size_t)written;

    for (int i = 0; i < sp; i++) {
        if (pos + 1 >= outsz) return -1;
        out[pos++] = '/';
        out[pos] = '\0';
        written = snprintf(out + pos, outsz - pos, "%s", stack[i]);
        if (written < 0 || (size_t)written >= (outsz - pos)) return -1;
        pos += (size_t)written;
    }
    return 0;
}

static int starts_with(const char *str, const char *prefix) {
    size_t ls = strlen(str), lp = strlen(prefix);
    if (lp > ls) return 0;
    if (strncmp(str, prefix, lp) != 0) return 0;
    /* Ensure boundary: either exact match or next char is '/' */
    if (ls == lp) return 1;
    return str[lp] == '/';
}

char* read_file_secure(const char *base_dir, const char *requested_path, size_t max_bytes) {
    if (!base_dir || !requested_path) {
        char *msg = strdup("ERROR: Invalid arguments.");
        return msg ? msg : NULL;
    }
    if (strlen(base_dir) == 0 || strlen(base_dir) > PATH_MAX) {
        char *msg = strdup("ERROR: Invalid base directory.");
        return msg ? msg : NULL;
    }
    if (strlen(requested_path) == 0 || strlen(requested_path) > PATH_MAX) {
        char *msg = strdup("ERROR: Invalid requested path.");
        return msg ? msg : NULL;
    }
    /* Base must exist, be directory, and not symlink */
    if (!is_directory_nofollow(base_dir)) {
        char *msg = strdup("ERROR: Base path is not a directory or does not exist.");
        return msg ? msg : NULL;
    }
    if (is_symlink_nofollow(base_dir)) {
        char *msg = strdup("ERROR: Base directory must not be a symbolic link.");
        return msg ? msg : NULL;
    }

    /* Get absolute base path (without resolving symlinks in parents if possible).
       We assume base_dir provided is absolute or relative; we'll make it absolute by chdir/getcwd dance safely. */
    char base_abs[PATH_MAX];
    if (base_dir[0] == '/') {
        strncpy(base_abs, base_dir, sizeof(base_abs) - 1);
        base_abs[sizeof(base_abs) - 1] = '\0';
    } else {
        char cwd[PATH_MAX];
        if (!getcwd(cwd, sizeof(cwd))) {
            char *msg = strdup("ERROR: Unable to get current working directory.");
            return msg ? msg : NULL;
        }
        int w = snprintf(base_abs, sizeof(base_abs), "%s/%s", cwd, base_dir);
        if (w < 0 || w >= (int)sizeof(base_abs)) {
            char *msg = strdup("ERROR: Base path too long.");
            return msg ? msg : NULL;
        }
    }

    /* Normalize combined path */
    char candidate[PATH_MAX];
    if (requested_path[0] == '/') {
        char *msg = strdup("ERROR: Absolute paths are not allowed.");
        return msg ? msg : NULL;
    }
    if (join_and_normalize(base_abs, requested_path, candidate, sizeof(candidate)) != 0) {
        char *msg = strdup("ERROR: Failed to normalize path.");
        return msg ? msg : NULL;
    }

    if (!starts_with(candidate, base_abs)) {
        char *msg = strdup("ERROR: Path traversal detected.");
        return msg ? msg : NULL;
    }

    /* Ensure path exists and is a regular file, with no symlinks along the path */
    if (access(candidate, F_OK) != 0) {
        char *msg = strdup("ERROR: File does not exist.");
        return msg ? msg : NULL;
    }

    /* Walk through each component and ensure no symlinks */
    char path_walk[PATH_MAX];
    strncpy(path_walk, base_abs, sizeof(path_walk) - 1);
    path_walk[sizeof(path_walk) - 1] = '\0';
    size_t base_len = strlen(base_abs);
    if (base_len > 1 && path_walk[base_len - 1] == '/') {
        path_walk[base_len - 1] = '\0';
    }

    if (strlen(candidate) > strlen(path_walk)) {
        const char *rel = candidate + strlen(path_walk) + ((strcmp(path_walk, "/") == 0) ? 0 : 1);
        char comp[PATH_MAX];
        const char *p = rel;
        while (*p) {
            const char *slash = strchr(p, '/');
            size_t clen = slash ? (size_t)(slash - p) : strlen(p);
            if (clen >= sizeof(comp)) {
                char *msg = strdup("ERROR: Component too long.");
                return msg ? msg : NULL;
            }
            memcpy(comp, p, clen);
            comp[clen] = '\0';
            size_t cur_len = strlen(path_walk);
            if (cur_len + 1 + clen + 1 >= sizeof(path_walk)) {
                char *msg = strdup("ERROR: Path too long.");
                return msg ? msg : NULL;
            }
            if (!(cur_len == 1 && path_walk[0] == '/')) {
                strncat(path_walk, "/", sizeof(path_walk) - strlen(path_walk) - 1);
            } else if (cur_len == 1 && path_walk[0] == '/') {
                /* root already has trailing slash */
            }
            strncat(path_walk, comp, sizeof(path_walk) - strlen(path_walk) - 1);

            if (is_symlink_nofollow(path_walk)) {
                char *msg = strdup("ERROR: Symbolic links are not allowed.");
                return msg ? msg : NULL;
            }
            if (!slash) break;
            p = slash + 1;
        }
    }

    if (!is_regular_nofollow(candidate)) {
        char *msg = strdup("ERROR: Not a regular file.");
        return msg ? msg : NULL;
    }

    int flags = O_RDONLY;
#ifdef O_NOFOLLOW
    flags |= O_NOFOLLOW;
#endif
    int fd = open(candidate, flags);
    if (fd < 0) {
        char *msg = strdup("ERROR: Unable to open file.");
        return msg ? msg : NULL;
    }

    struct stat st;
    if (fstat(fd, &st) != 0) {
        close(fd);
        char *msg = strdup("ERROR: Unable to stat file.");
        return msg ? msg : NULL;
    }
    if (!S_ISREG(st.st_mode)) {
        close(fd);
        char *msg = strdup("ERROR: Not a regular file.");
        return msg ? msg : NULL;
    }
    if ((size_t)st.st_size > max_bytes) {
        close(fd);
        char *msg = strdup("ERROR: File too large.");
        return msg ? msg : NULL;
    }

    size_t cap = (size_t)st.st_size;
    if (cap == 0) cap = 1;
    if (cap > max_bytes) cap = max_bytes;

    char *buffer = (char*)malloc(cap + 1);
    if (!buffer) {
        close(fd);
        char *msg = strdup("ERROR: Out of memory.");
        return msg ? msg : NULL;
    }

    size_t total = 0;
    while (1) {
        size_t to_read = 8192;
        if (to_read > max_bytes - total) to_read = max_bytes - total;
        if (to_read == 0) break;
        ssize_t r = read(fd, buffer + total, to_read);
        if (r < 0) {
            free(buffer);
            close(fd);
            char *msg = strdup("ERROR: Read failed.");
            return msg ? msg : NULL;
        }
        if (r == 0) break;
        total += (size_t)r;
        if (total > max_bytes) {
            free(buffer);
            close(fd);
            char *msg = strdup("ERROR: File grew beyond allowed size during read.");
            return msg ? msg : NULL;
        }
    }
    buffer[total] = '\0';
    close(fd);
    return buffer;
}

/* Helper to write text file safely */
static int write_text_file(const char *path, const char *text) {
    FILE *f = fopen(path, "wb");
    if (!f) return -1;
    size_t len = strlen(text);
    if (fwrite(text, 1, len, f) != len) {
        fclose(f);
        return -1;
    }
    fclose(f);
    return 0;
}

int main(int argc, char **argv) {
    if (argc >= 3) {
        char *content = read_file_secure(argv[1], argv[2], DEFAULT_MAX_BYTES);
        if (content) {
            printf("%s\n", content);
            free(content);
        } else {
            printf("ERROR: Unknown error.\n");
        }
        return 0;
    }

    /* Self-tests (5 cases) */
    char base[PATH_MAX];
    snprintf(base, sizeof(base), "/tmp/secure_read_base_c_%d", getpid());
    mkdir(base, 0700);

    char file1[PATH_MAX], sub[PATH_MAX], file2[PATH_MAX], outside[PATH_MAX], linkpath[PATH_MAX];
    snprintf(file1, sizeof(file1), "%s/file1.txt", base);
    snprintf(sub, sizeof(sub), "%s/sub", base);
    mkdir(sub, 0700);
    snprintf(file2, sizeof(file2), "%s/note.txt", sub);
    write_text_file(file1, "Hello world from file1");
    write_text_file(file2, "Nested content");

    printf("---- Test 1: Read simple file ----\n");
    char *res1 = read_file_secure(base, "file1.txt", DEFAULT_MAX_BYTES);
    if (res1) { printf("%s\n", res1); free(res1); }

    printf("---- Test 2: Read nested file ----\n");
    char *res2 = read_file_secure(base, "sub/note.txt", DEFAULT_MAX_BYTES);
    if (res2) { printf("%s\n", res2); free(res2); }

    printf("---- Test 3: Path traversal attempt ----\n");
    char *res3 = read_file_secure(base, "../etc/passwd", DEFAULT_MAX_BYTES);
    if (res3) { printf("%s\n", res3); free(res3); }

    printf("---- Test 4: Read directory (should fail) ----\n");
    char *res4 = read_file_secure(base, "sub", DEFAULT_MAX_BYTES);
    if (res4) { printf("%s\n", res4); free(res4); }

    printf("---- Test 5: Read symlink (should fail) ----\n");
    snprintf(outside, sizeof(outside), "%s/outside.txt", base);
    write_text_file(outside, "Outside content");
    snprintf(linkpath, sizeof(linkpath), "%s/link_to_outside", base);
    int symlink_supported = 1;
    if (unlink(linkpath) != 0 && errno != ENOENT) { /* ignore */ }
    if (symlink("outside.txt", linkpath) != 0) {
        symlink_supported = 0;
    }
    if (symlink_supported) {
        char *res5 = read_file_secure(base, "link_to_outside", DEFAULT_MAX_BYTES);
        if (res5) { printf("%s\n", res5); free(res5); }
    } else {
        printf("SKIPPED: Symlink not supported or permission denied\n");
    }

    /* Cleanup (best-effort) */
    unlink(linkpath);
    unlink(file1);
    unlink(file2);
    unlink(outside);
    rmdir(sub);
    rmdir(base);
    return 0;
}