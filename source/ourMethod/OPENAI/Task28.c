#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static void trim_inplace(char *s) {
    if (!s) return;
    size_t len = strlen(s);
    size_t start = 0;
    while (start < len && isspace((unsigned char)s[start])) start++;
    size_t end = len;
    while (end > start && isspace((unsigned char)s[end - 1])) end--;
    size_t newlen = end > start ? (end - start) : 0;
    if (start > 0 && newlen > 0) {
        memmove(s, s + start, newlen);
    }
    s[newlen] = '\0';
}

static void sanitize_name(const char *src, char *dst, size_t dst_size) {
    if (!dst || dst_size == 0) return;
    if (!src) {
        dst[0] = '\0';
        return;
    }
    size_t count = 0;
    for (size_t i = 0; src[i] != '\0' && count + 1 < dst_size; ++i) {
        unsigned char ch = (unsigned char)src[i];
        if (!iscntrl(ch)) {
            dst[count++] = (char)ch;
            if (count >= 100) break; // cap to 100 chars
        }
    }
    dst[count] = '\0';
    trim_inplace(dst);
}

static char* dup_cstr(const char* s) {
    if (!s) return NULL;
    size_t len = strlen(s);
    char* out = (char*)malloc(len + 1);
    if (!out) return NULL;
    memcpy(out, s, len + 1);
    return out;
}

char* likes_text(const char **names, size_t count) {
    if (names == NULL || count == 0) {
        char* res = dup_cstr("no one likes this");
        if (!res) return dup_cstr("allocation failed");
        return res;
    }

    char a[101], b[101], c[101];
    if (count >= 1) sanitize_name(names[0], a, sizeof(a)); else a[0] = '\0';
    if (count >= 2) sanitize_name(names[1], b, sizeof(b)); else b[0] = '\0';
    if (count >= 3) sanitize_name(names[2], c, sizeof(c)); else c[0] = '\0';

    int needed = 0;
    if (count == 1) {
        needed = snprintf(NULL, 0, "%s likes this", a);
        if (needed < 0) return dup_cstr("formatting error");
        char* out = (char*)malloc((size_t)needed + 1);
        if (!out) return dup_cstr("allocation failed");
        snprintf(out, (size_t)needed + 1, "%s likes this", a);
        return out;
    } else if (count == 2) {
        needed = snprintf(NULL, 0, "%s and %s like this", a, b);
        if (needed < 0) return dup_cstr("formatting error");
        char* out = (char*)malloc((size_t)needed + 1);
        if (!out) return dup_cstr("allocation failed");
        snprintf(out, (size_t)needed + 1, "%s and %s like this", a, b);
        return out;
    } else if (count == 3) {
        needed = snprintf(NULL, 0, "%s, %s and %s like this", a, b, c);
        if (needed < 0) return dup_cstr("formatting error");
        char* out = (char*)malloc((size_t)needed + 1);
        if (!out) return dup_cstr("allocation failed");
        snprintf(out, (size_t)needed + 1, "%s, %s and %s like this", a, b, c);
        return out;
    } else {
        size_t others = count - 2;
        needed = snprintf(NULL, 0, "%s, %s and %zu others like this", a, b, others);
        if (needed < 0) return dup_cstr("formatting error");
        char* out = (char*)malloc((size_t)needed + 1);
        if (!out) return dup_cstr("allocation failed");
        snprintf(out, (size_t)needed + 1, "%s, %s and %zu others like this", a, b, others);
        return out;
    }
}

int main(void) {
    // 5 test cases
    const char **empty = NULL;
    char *r0 = likes_text(empty, 0);
    printf("[] --> %s\n", r0);
    free(r0);

    const char *t1[] = {"Peter"};
    char *r1 = likes_text(t1, 1);
    printf("[Peter] --> %s\n", r1);
    free(r1);

    const char *t2[] = {"Jacob", "Alex"};
    char *r2 = likes_text(t2, 2);
    printf("[Jacob, Alex] --> %s\n", r2);
    free(r2);

    const char *t3[] = {"Max", "John", "Mark"};
    char *r3 = likes_text(t3, 3);
    printf("[Max, John, Mark] --> %s\n", r3);
    free(r3);

    const char *t4[] = {"Alex", "Jacob", "Mark", "Max"};
    char *r4 = likes_text(t4, 4);
    printf("[Alex, Jacob, Mark, Max] --> %s\n", r4);
    free(r4);

    return 0;
}