/*
Secure file reader in C that reads a file specified by a user-provided relative path
within a base directory and prints its contents to stdout. It prevents directory
traversal, rejects symlinks, ensures the target is a regular file, and uses bounded I/O.

Build:
  cc -Wall -Wextra -O2 -o task36 task36.c

Run:
  ./task36
This program includes 5 test cases in main(). Modify as needed.
*/

#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#ifndef NAME_MAX
#define NAME_MAX 255
#endif

#ifndef O_NOFOLLOW
#define O_NOFOLLOW 0
#endif

#ifndef O_CLOEXEC
#define O_CLOEXEC 0
#endif

#define MAX_TOTAL_READ (10U * 1024U * 1024U) /* 10 MiB safety cap */
#define READ_CHUNK 8192

static int validate_user_path(const char *path) {
    if (path == NULL) return -1;
    size_t len = strnlen(path, PATH_MAX + 1);
    if (len == 0 || len > PATH_MAX) return -1;
    if (path[0] == '/') return -1; /* absolute paths not allowed */
    if (path[len - 1] == '/') return -1; /* trailing slash not allowed for file */
    return 0;
}

static int is_special_component(const char *s, size_t len) {
    if (len == 1 && s[0] == '.') return 1;
    if (len == 2 && s[0] == '.' && s[1] == '.') return 1;
    return 0;
}

/* Securely open a file relative to base_fd by walking components without
   allowing symlinks or traversal outside the base. Returns file fd on success, -1 on error. */
static int secure_open_relative(int base_fd, const char *rel_path) {
    if (validate_user_path(rel_path) != 0) {
        errno = EINVAL;
        return -1;
    }

    /* Copy path to a local buffer for safe parsing */
    char pathbuf[PATH_MAX + 1];
    size_t rel_len = strnlen(rel_path, PATH_MAX);
    if (rel_len > PATH_MAX) {
        errno = ENAMETOOLONG;
        return -1;
    }
    memcpy(pathbuf, rel_path, rel_len);
    pathbuf[rel_len] = '\0';

    /* Start at base directory */
    int dirfd = dup(base_fd);
    if (dirfd < 0) {
        return -1;
    }

    /* Iterate components */
    char *p = pathbuf;
    char *save = p;
    int fd = -1;

    while (*p != '\0') {
        /* Find next '/' or end */
        char *slash = strchr(save, '/');
        size_t comp_len = (slash != NULL) ? (size_t)(slash - save) : strnlen(save, PATH_MAX + 1);

        if (comp_len == 0) {
            /* Skip repeated slashes (shouldn't happen since we disallow leading/trailing) */
            if (slash) {
                save = slash + 1;
                continue;
            } else {
                break;
            }
        }

        if (comp_len > NAME_MAX) {
            close(dirfd);
            errno = ENAMETOOLONG;
            return -1;
        }

        if (is_special_component(save, comp_len)) {
            close(dirfd);
            errno = EPERM; /* reject '.' or '..' */
            return -1;
        }

        /* Determine if this is the last component */
        int last = (slash == NULL || *(slash + 1) == '\0');

        /* Build component as a temporary string */
        char comp[NAME_MAX + 1];
        memcpy(comp, save, comp_len);
        comp[comp_len] = '\0';

        if (!last) {
            /* Intermediate component: must be a directory; reject symlinks */
            int nextdir = openat(dirfd, comp, O_RDONLY | O_DIRECTORY | O_NOFOLLOW | O_CLOEXEC);
            if (nextdir < 0) {
                int saved = errno;
                close(dirfd);
                errno = saved;
                return -1;
            }
            close(dirfd);
            dirfd = nextdir;
        } else {
            /* Final component: open as regular file; reject symlink and directory */
            fd = openat(dirfd, comp, O_RDONLY | O_NOFOLLOW | O_CLOEXEC);
            int saved_open_errno = errno;
            close(dirfd);
            if (fd < 0) {
                errno = saved_open_errno;
                return -1;
            }
            struct stat st;
            if (fstat(fd, &st) != 0) {
                int saved = errno;
                close(fd);
                errno = saved;
                return -1;
            }
            if (!S_ISREG(st.st_mode)) {
                close(fd);
                errno = EISDIR; /* or EPERM: not a regular file */
                return -1;
            }
            return fd; /* success */
        }

        /* Advance past slash */
        if (slash) {
            save = slash + 1;
            p = save;
        } else {
            break;
        }
    }

    /* If we reach here, path ended unexpectedly */
    close(dirfd);
    errno = EINVAL;
    return -1;
}

/* Copies up to max_bytes from fd to stdout. Returns 0 on success, non-zero on error. */
static int copy_fd_to_stdout(int fd, size_t max_bytes) {
    if (max_bytes == 0 || max_bytes > MAX_TOTAL_READ) {
        max_bytes = MAX_TOTAL_READ;
    }

    unsigned char buf[READ_CHUNK];
    size_t remaining = max_bytes;

    while (remaining > 0) {
        size_t to_read = READ_CHUNK;
        if (to_read > remaining) to_read = remaining;

        ssize_t r = read(fd, buf, to_read);
        if (r < 0) {
            return -1;
        } else if (r == 0) {
            break; /* EOF */
        }

        size_t written_total = 0;
        while (written_total < (size_t)r) {
            size_t w = fwrite(buf + written_total, 1, (size_t)r - written_total, stdout);
            if (w == 0) {
                if (ferror(stdout)) {
                    return -1;
                }
            }
            written_total += w;
        }

        if (remaining >= (size_t)r) remaining -= (size_t)r;
        else remaining = 0;
    }

    /* Flush stdout to ensure output is visible */
    if (fflush(stdout) != 0) return -1;
    return 0;
}

/* Public API: read a file specified by user_path within base_dir and print its contents. */
int read_and_print_file(const char *base_dir, const char *user_path, size_t max_bytes) {
    if (base_dir == NULL || user_path == NULL) {
        errno = EINVAL;
        return -1;
    }

    size_t base_len = strnlen(base_dir, PATH_MAX + 1);
    if (base_len == 0 || base_len > PATH_MAX) {
        errno = EINVAL;
        return -1;
    }

    /* Open base directory securely */
    int basefd = open(base_dir, O_RDONLY | O_DIRECTORY | O_CLOEXEC);
    if (basefd < 0) {
        return -1;
    }

    int fd = secure_open_relative(basefd, user_path);
    int saved_err = errno;
    close(basefd);
    if (fd < 0) {
        errno = saved_err;
        return -1;
    }

    int rc = copy_fd_to_stdout(fd, max_bytes);
    saved_err = errno;
    close(fd);
    errno = saved_err;

    return rc;
}

/* Helpers for tests */
static int mkdir_p(const char *path, mode_t mode) {
    if (!path || !*path) return -1;
    char tmp[PATH_MAX + 1];
    size_t len = strnlen(path, PATH_MAX);
    if (len == 0 || len > PATH_MAX) return -1;
    memcpy(tmp, path, len);
    tmp[len] = '\0';

    for (char *p = tmp + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';
            if (mkdir(tmp, mode) != 0 && errno != EEXIST) return -1;
            *p = '/';
        }
    }
    if (mkdir(tmp, mode) != 0 && errno != EEXIST) return -1;
    return 0;
}

static int write_text_file(const char *path, const char *content) {
    if (!path || !content) return -1;
    FILE *f = fopen(path, "w");
    if (!f) return -1;
    size_t len = strlen(content);
    size_t w = fwrite(content, 1, len, f);
    int rc = 0;
    if (w != len) rc = -1;
    if (fflush(f) != 0) rc = -1;
    if (fclose(f) != 0) rc = -1;
    return rc;
}

static int join_path(char *out, size_t outsz, const char *a, const char *b) {
    if (!out || !a || !b) return -1;
    size_t la = strnlen(a, PATH_MAX);
    size_t lb = strnlen(b, PATH_MAX);
    if (la == 0 || la > PATH_MAX || lb > PATH_MAX) return -1;

    int need_slash = (a[la - 1] != '/');
    size_t total = la + (need_slash ? 1 : 0) + lb + 1;
    if (total > outsz) {
        errno = ENAMETOOLONG;
        return -1;
    }

    memcpy(out, a, la);
    size_t pos = la;
    if (need_slash) out[pos++] = '/';
    memcpy(out + pos, b, lb);
    pos += lb;
    out[pos] = '\0';
    return 0;
}

int main(void) {
    /* Create temporary base directory */
    char templ[] = "/tmp/task36_base_XXXXXX";
    char *base_dir = mkdtemp(templ);
    if (!base_dir) {
        fprintf(stderr, "Failed to create temp dir: %s\n", strerror(errno));
        return 1;
    }

    /* Prepare test files */
    char path[PATH_MAX + 1];

    /* Create "a.txt" with content */
    if (join_path(path, sizeof(path), base_dir, "a.txt") != 0 ||
        write_text_file(path, "Hello from a.txt\n") != 0) {
        fprintf(stderr, "Failed to create a.txt: %s\n", strerror(errno));
        return 1;
    }

    /* Create directory "dir" and file "dir/b.txt" */
    if (join_path(path, sizeof(path), base_dir, "dir") != 0 || mkdir_p(path, 0700) != 0) {
        fprintf(stderr, "Failed to create dir: %s\n", strerror(errno));
        return 1;
    }
    if (join_path(path, sizeof(path), base_dir, "dir/b.txt") != 0 ||
        write_text_file(path, "Nested file b.txt content\n") != 0) {
        fprintf(stderr, "Failed to create dir/b.txt: %s\n", strerror(errno));
        return 1;
    }

    /* Create symlink "link_to_a.txt" -> "a.txt" (may fail on some systems; handled in test) */
    char linkpath[PATH_MAX + 1];
    if (join_path(linkpath, sizeof(linkpath), base_dir, "link_to_a.txt") == 0) {
        /* Target relative to link location */
        if (symlink("a.txt", linkpath) != 0) {
            /* Not fatal for tests */
        }
    }

    /* Test 1: normal file read */
    printf("---- Test 1: Read a.txt (expected: content shown) ----\n");
    if (read_and_print_file(base_dir, "a.txt", MAX_TOTAL_READ) != 0) {
        fprintf(stderr, "Test 1 failed: %s\n", strerror(errno));
    }

    /* Test 2: read nested file */
    printf("---- Test 2: Read dir/b.txt (expected: content shown) ----\n");
    if (read_and_print_file(base_dir, "dir/b.txt", MAX_TOTAL_READ) != 0) {
        fprintf(stderr, "Test 2 failed: %s\n", strerror(errno));
    }

    /* Test 3: directory traversal attempt (should fail) */
    printf("---- Test 3: Traversal attempt '../a.txt' (expected: error) ----\n");
    if (read_and_print_file(base_dir, "../a.txt", MAX_TOTAL_READ) != 0) {
        fprintf(stderr, "Test 3 correctly failed: %s\n", strerror(errno));
    } else {
        fprintf(stderr, "Test 3 unexpectedly succeeded\n");
    }

    /* Test 4: symlink (should be rejected) */
    printf("---- Test 4: Symlink 'link_to_a.txt' (expected: error) ----\n");
    int rc4 = read_and_print_file(base_dir, "link_to_a.txt", MAX_TOTAL_READ);
    if (rc4 != 0) {
        fprintf(stderr, "Test 4 correctly failed (or symlink not created): %s\n", strerror(errno));
    } else {
        fprintf(stderr, "Test 4 unexpectedly succeeded\n");
    }

    /* Test 5: directory path (should be rejected) */
    printf("---- Test 5: Directory 'dir' (expected: error) ----\n");
    if (read_and_print_file(base_dir, "dir", MAX_TOTAL_READ) != 0) {
        fprintf(stderr, "Test 5 correctly failed: %s\n", strerror(errno));
    } else {
        fprintf(stderr, "Test 5 unexpectedly succeeded\n");
    }

    /* Cleanup (best-effort) */
    if (join_path(path, sizeof(path), base_dir, "dir/b.txt") == 0) unlink(path);
    if (join_path(path, sizeof(path), base_dir, "dir") == 0) rmdir(path);
    if (join_path(path, sizeof(path), base_dir, "a.txt") == 0) unlink(path);
    if (join_path(path, sizeof(path), base_dir, "link_to_a.txt") == 0) unlink(path);
    rmdir(base_dir);

    return 0;
}