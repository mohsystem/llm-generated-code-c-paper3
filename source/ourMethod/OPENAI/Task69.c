#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/types.h>

// Return codes:
// 0 = success
// 1 = invalid input
// 2 = target path resolves outside base
// 3 = file not found
// 4 = not a regular file
// 5 = is a symlink
// 6 = delete failed

static int sanitize_relative(const char* user, char* out, size_t outsz) {
    if (!user || !out || outsz == 0) return -1;
    size_t n = strlen(user);
    if (n == 0 || n > 4096) return -1;
    if (user[0] == '/') return -1; // absolute not allowed
    // reject control chars
    for (size_t i = 0; i < n; ++i) {
        unsigned char c = (unsigned char)user[i];
        if (c < 32) return -1;
    }
    // Build normalized relative path rejecting ".."
    out[0] = '\0';
    char buf[PATH_MAX];
    if (sizeof(buf) <= n) return -1;
    memcpy(buf, user, n + 1);
    char* saveptr = NULL;
    char* token = strtok_r(buf, "/\\", &saveptr);
    int first = 1;
    while (token) {
        if (strcmp(token, ".") == 0 || strcmp(token, "") == 0) {
            // skip
        } else if (strcmp(token, "..") == 0) {
            return -1;
        } else {
            size_t need = strlen(out) + (first ? 0 : 1) + strlen(token) + 1;
            if (need > outsz) return -1;
            if (!first) strcat(out, "/");
            strcat(out, token);
            first = 0;
        }
        token = strtok_r(NULL, "/\\", &saveptr);
    }
    if (out[0] == '\0') {
        // allow deleting a file at base root only if specified explicitly (reject empty)
        return -1;
    }
    return 0;
}

static int starts_with_path(const char* base, const char* target) {
    size_t lb = strlen(base);
    size_t lt = strlen(target);
    if (lb == 0 || lt == 0) return 0;
    if (strncmp(base, target, lb) != 0) return 0;
    // Ensure boundary: either equal or next char is '/'
    if (lt == lb) return 1;
    return target[lb] == '/';
}

int secure_delete(const char* baseDir, const char* userPath) {
    if (!baseDir || !userPath) return 1;
    if (strlen(baseDir) == 0 || strlen(userPath) == 0) return 1;

    char baseReal[PATH_MAX];
    if (!realpath(baseDir, baseReal)) {
        return 1;
    }

    char rel[PATH_MAX];
    if (sanitize_relative(userPath, rel, sizeof(rel)) != 0) {
        return 1;
    }

    // Construct target path
    char target[PATH_MAX];
    int r = snprintf(target, sizeof(target), "%s/%s", baseReal, rel);
    if (r <= 0 || (size_t)r >= sizeof(target)) return 1;

    // Ensure target stays within base
    if (!starts_with_path(baseReal, target)) {
        return 2;
    }

    // lstat to avoid following symlinks
    struct stat st;
    if (lstat(target, &st) != 0) {
        if (errno == ENOENT) return 3;
        return 6;
    }
    if (S_ISLNK(st.st_mode)) return 5;
    if (!S_ISREG(st.st_mode)) return 4;

    // Open parent directory safely
    char parent[PATH_MAX];
    char name[NAME_MAX + 1];
    // Split into parent and filename
    const char* slash = strrchr(target, '/');
    if (!slash) return 1;
    size_t parent_len = (size_t)(slash - target);
    if (parent_len >= sizeof(parent)) return 1;
    memcpy(parent, target, parent_len);
    parent[parent_len] = '\0';
    size_t name_len = strlen(slash + 1);
    if (name_len == 0 || name_len > NAME_MAX) return 1;
    memcpy(name, slash + 1, name_len + 1);

    int dfd = open(parent, O_RDONLY | O_DIRECTORY | O_CLOEXEC);
    if (dfd < 0) {
        return 6;
    }

    // Re-validate target via fstatat without following symlinks
    struct stat st2;
    if (fstatat(dfd, name, &st2, AT_SYMLINK_NOFOLLOW) != 0) {
        int e = errno;
        close(dfd);
        if (e == ENOENT) return 3;
        return 6;
    }
    if (S_ISLNK(st2.st_mode)) {
        close(dfd);
        return 5;
    }
    if (!S_ISREG(st2.st_mode)) {
        close(dfd);
        return 4;
    }

    // Unlink relative to directory fd
    if (unlinkat(dfd, name, 0) != 0) {
        int e = errno;
        close(dfd);
        if (e == ENOENT) return 3;
        return 6;
    }
    close(dfd);
    return 0;
}

static int write_text(const char* path, const char* text) {
    FILE* f = fopen(path, "wb");
    if (!f) return -1;
    size_t n = fwrite(text, 1, strlen(text), f);
    fclose(f);
    return (int)n == (int)strlen(text) ? 0 : -1;
}

int main(int argc, char** argv) {
    // Setup test environment
    char templ[] = "/tmp/safe-del-c-XXXXXX";
    char* base = mkdtemp(templ);
    if (!base) {
        printf("Setup failed\n");
        return 1;
    }
    char f1[PATH_MAX], sub[PATH_MAX], nested[PATH_MAX], f2[PATH_MAX], sym[PATH_MAX];
    snprintf(f1, sizeof(f1), "%s/file1.txt", base);
    snprintf(sub, sizeof(sub), "%s/sub", base);
    mkdir(sub, 0700);
    snprintf(nested, sizeof(nested), "%s/inside.txt", sub);
    snprintf(f2, sizeof(f2), "%s/file2.txt", base);
    snprintf(sym, sizeof(sym), "%s/link_to_file2", base);

    write_text(f1, "one");
    write_text(nested, "two");
    write_text(f2, "three");
    // Create symlink if possible
    symlink("file2.txt", sym); // ignore error if not supported

    const char* tests[5][2] = {
        { base, "file1.txt" },        // success
        { base, "sub/inside.txt" },   // success
        { base, "sub" },              // reject: directory
        { base, "link_to_file2" },    // reject: symlink (if created) else not found
        { base, "../outside.txt" }    // reject: traversal
    };

    for (int i = 0; i < 5; ++i) {
        int rc = secure_delete(tests[i][0], tests[i][1]);
        printf("Test %d => %d\n", i + 1, rc);
    }

    // CLI mode: expect baseDir and userPath
    if (argc >= 3) {
        int rc = secure_delete(argv[1], argv[2]);
        printf("%d\n", rc);
    }

    // Cleanup
    // Remove remaining files and directories
    unlink(f2);
    unlink(sym);
    unlink(nested);
    rmdir(sub);
    rmdir(base);
    return 0;
}