#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>

#define NAME_MIN_LEN 1
#define NAME_MAX_LEN 50
#define AGE_MIN 0
#define AGE_MAX 120
#define NUM_MIN (-1000000)
#define NUM_MAX (1000000)
#define NUM_COUNT_MIN 1
#define NUM_COUNT_MAX 100
#define INPUT_MAX_LEN 1024

static void rstrip_newline(char *s) {
    if (!s) return;
    size_t len = strlen(s);
    while (len > 0 && (s[len-1] == '\n' || s[len-1] == '\r')) {
        s[len-1] = '\0';
        len--;
    }
}

static void collapse_spaces(const char *in, char *out, size_t out_size) {
    size_t oi = 0;
    int prev_space = 0;
    for (size_t i = 0; in[i] != '\0'; i++) {
        char c = in[i];
        if (c == ' ') {
            if (!prev_space) {
                if (oi + 1 < out_size) out[oi++] = c;
                prev_space = 1;
            }
        } else {
            if (oi + 1 < out_size) out[oi++] = c;
            prev_space = 0;
        }
    }
    if (oi < out_size) out[oi] = '\0';
    else if (out_size > 0) out[out_size - 1] = '\0';
}

static void trim_spaces(const char *in, char *out, size_t out_size) {
    size_t len = strlen(in);
    size_t start = 0;
    while (start < len && isspace((unsigned char)in[start])) start++;
    size_t end = len;
    while (end > start && isspace((unsigned char)in[end - 1])) end--;
    size_t n = end - start;
    if (n + 1 > out_size) n = out_size - 1;
    memcpy(out, in + start, n);
    out[n] = '\0';
}

static int is_allowed_name_char(char c) {
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) return 1;
    if (c == ' ' || c == '-' || c == '\'') return 1;
    return 0;
}

static int validate_name(const char *in, char *out, size_t out_size, char *err, size_t err_size) {
    if (!in || !out || out_size == 0) {
        snprintf(err, err_size, "%s", "Invalid parameters.");
        return -1;
    }
    char trimmed[INPUT_MAX_LEN + 1];
    trim_spaces(in, trimmed, sizeof(trimmed));
    char collapsed[INPUT_MAX_LEN + 1];
    collapse_spaces(trimmed, collapsed, sizeof(collapsed));
    size_t len = strlen(collapsed);
    if (len < NAME_MIN_LEN || len > NAME_MAX_LEN) {
        snprintf(err, err_size, "%s", "Name must be between 1 and 50 characters after trimming.");
        return -1;
    }
    for (size_t i = 0; i < len; i++) {
        if (!is_allowed_name_char(collapsed[i])) {
            snprintf(err, err_size, "Name contains invalid character: '%c'", collapsed[i]);
            return -1;
        }
    }
    if (len + 1 > out_size) {
        snprintf(err, err_size, "%s", "Output buffer too small for name.");
        return -1;
    }
    memcpy(out, collapsed, len + 1);
    return 0;
}

static int validate_age(const char *in, int *age_out, char *err, size_t err_size) {
    if (!in || !age_out) {
        snprintf(err, err_size, "%s", "Invalid parameters.");
        return -1;
    }
    char tbuf[64];
    trim_spaces(in, tbuf, sizeof(tbuf));
    size_t len = strlen(tbuf);
    if (len == 0 || len > 3) {
        snprintf(err, err_size, "%s", "Age format invalid.");
        return -1;
    }
    char *endptr = NULL;
    long val = strtol(tbuf, &endptr, 10);
    if (endptr == tbuf || *endptr != '\0') {
        snprintf(err, err_size, "%s", "Age must be an integer.");
        return -1;
    }
    if (val < AGE_MIN || val > AGE_MAX) {
        snprintf(err, err_size, "%s", "Age must be between 0 and 120.");
        return -1;
    }
    *age_out = (int)val;
    return 0;
}

static int is_delim(char c) {
    return (c == ',' || c == ' ' || c == '\t' || c == '\r' || c == '\n');
}

static int parse_numbers(const char *in, int *out_arr, size_t *out_count, char *err, size_t err_size) {
    if (!in || !out_arr || !out_count) {
        snprintf(err, err_size, "%s", "Invalid parameters.");
        return -1;
    }
    char buf[INPUT_MAX_LEN + 1];
    // Trim leading/trailing spaces
    char tmp[INPUT_MAX_LEN + 1];
    strncpy(tmp, in, sizeof(tmp) - 1);
    tmp[sizeof(tmp) - 1] = '\0';
    trim_spaces(tmp, buf, sizeof(buf));
    if (buf[0] == '\0') {
        snprintf(err, err_size, "%s", "Numbers input is empty.");
        return -1;
    }
    size_t count = 0;
    size_t i = 0;
    size_t len = strlen(buf);
    while (i < len) {
        while (i < len && is_delim(buf[i])) i++;
        if (i >= len) break;
        if (count >= NUM_COUNT_MAX) {
            snprintf(err, err_size, "%s", "Provide between 1 and 100 numbers.");
            return -1;
        }
        char token[64];
        size_t ti = 0;
        while (i < len && !is_delim(buf[i]) && ti + 1 < sizeof(token)) {
            token[ti++] = buf[i++];
        }
        token[ti] = '\0';
        if (ti == 0) {
            snprintf(err, err_size, "%s", "Invalid empty number token.");
            return -1;
        }
        char *endptr = NULL;
        long val = strtol(token, &endptr, 10);
        if (endptr == token || *endptr != '\0') {
            snprintf(err, err_size, "Invalid integer: %s", token);
            return -1;
        }
        if (val < NUM_MIN || val > NUM_MAX) {
            snprintf(err, err_size, "Number out of range: %ld", val);
            return -1;
        }
        out_arr[count++] = (int)val;
    }
    if (count < NUM_COUNT_MIN) {
        snprintf(err, err_size, "%s", "Provide between 1 and 100 numbers.");
        return -1;
    }
    *out_count = count;
    return 0;
}

static int cmp_ints(const void *a, const void *b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

struct DynBuf {
    char *data;
    size_t size;
    size_t cap;
};

static int db_init(struct DynBuf *db) {
    db->cap = 256;
    db->size = 0;
    db->data = (char*)malloc(db->cap);
    if (!db->data) return -1;
    db->data[0] = '\0';
    return 0;
}

static void db_free(struct DynBuf *db) {
    if (db->data) free(db->data);
    db->data = NULL;
    db->size = db->cap = 0;
}

static int db_ensure(struct DynBuf *db, size_t extra) {
    if (db->size + extra + 1 <= db->cap) return 0;
    size_t newcap = db->cap;
    while (db->size + extra + 1 > newcap) {
        if (newcap > SIZE_MAX / 2) return -1;
        newcap *= 2;
    }
    char *nd = (char*)realloc(db->data, newcap);
    if (!nd) return -1;
    db->data = nd;
    db->cap = newcap;
    return 0;
}

#include <stdarg.h>
static int db_appendf(struct DynBuf *db, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    va_list ap2;
    va_copy(ap2, ap);
    int need = vsnprintf(NULL, 0, fmt, ap2);
    va_end(ap2);
    if (need < 0) { va_end(ap); return -1; }
    if (db_ensure(db, (size_t)need) != 0) { va_end(ap); return -1; }
    int written = vsnprintf(db->data + db->size, db->cap - db->size, fmt, ap);
    va_end(ap);
    if (written < 0) return -1;
    db->size += (size_t)written;
    return 0;
}

static char* process_user_data(const char *name, int age, const int *nums, size_t count) {
    if (!name || !nums || count < NUM_COUNT_MIN || count > NUM_COUNT_MAX) {
        return NULL;
    }
    if (age < AGE_MIN || age > AGE_MAX) return NULL;
    for (size_t i = 0; i < count; i++) {
        if (nums[i] < NUM_MIN || nums[i] > NUM_MAX) return NULL;
    }

    long long sum = 0;
    int mn = nums[0];
    int mx = nums[0];
    int evens = 0, odds = 0;
    for (size_t i = 0; i < count; i++) {
        int v = nums[i];
        sum += v;
        if (v < mn) mn = v;
        if (v > mx) mx = v;
        if ((v & 1) == 0) evens++; else odds++;
    }
    double avg = (double)sum / (double)count;

    int *sorted = (int*)malloc(sizeof(int) * count);
    if (!sorted) return NULL;
    for (size_t i = 0; i < count; i++) sorted[i] = nums[i];
    qsort(sorted, count, sizeof(int), cmp_ints);

    double median;
    if (count % 2 == 1) {
        median = (double)sorted[count / 2];
    } else {
        median = ((double)sorted[count / 2 - 1] + (double)sorted[count / 2]) / 2.0;
    }

    // Build unique sorted
    int *uniq = (int*)malloc(sizeof(int) * count);
    if (!uniq) { free(sorted); return NULL; }
    size_t ucount = 0;
    for (size_t i = 0; i < count; i++) {
        if (i == 0 || sorted[i] != sorted[i - 1]) {
            uniq[ucount++] = sorted[i];
        }
    }

    struct DynBuf db;
    if (db_init(&db) != 0) { free(sorted); free(uniq); return NULL; }
    if (db_appendf(&db, "Result for %s\n", name) != 0) { db_free(&db); free(sorted); free(uniq); return NULL; }
    if (db_appendf(&db, "Age next year: %d\n", age + 1) != 0) { db_free(&db); free(sorted); free(uniq); return NULL; }
    if (db_appendf(&db, "Count: %zu, Min: %d, Max: %d, Sum: %lld, Average: %.2f, Median: %.2f\n",
                   count, mn, mx, (long long)sum, avg, median) != 0) { db_free(&db); free(sorted); free(uniq); return NULL; }
    if (db_appendf(&db, "Evens: %d, Odds: %d\n", evens, odds) != 0) { db_free(&db); free(sorted); free(uniq); return NULL; }
    if (db_appendf(&db, "Unique sorted: [") != 0) { db_free(&db); free(sorted); free(uniq); return NULL; }
    for (size_t i = 0; i < ucount; i++) {
        if (db_appendf(&db, "%d%s", uniq[i], (i + 1 < ucount) ? ", " : "") != 0) { db_free(&db); free(sorted); free(uniq); return NULL; }
    }
    if (db_appendf(&db, "]") != 0) { db_free(&db); free(sorted); free(uniq); return NULL; }

    free(sorted);
    free(uniq);
    return db.data; // ownership transferred; caller frees
}

static int safe_readline(char *buf, size_t size) {
    if (!fgets(buf, (int)size, stdin)) {
        return -1;
    }
    rstrip_newline(buf);
    if (strlen(buf) >= size - 1) {
        // line may have been truncated
        return -2;
    }
    if (strlen(buf) > INPUT_MAX_LEN) {
        return -3;
    }
    return 0;
}

static void run_test(const char *name_in, int age, const int *nums, size_t count, const char *label) {
    char name[NAME_MAX_LEN + 1];
    char err[128];
    printf("== %s ==\n", label);
    if (validate_name(name_in, name, sizeof(name), err, sizeof(err)) != 0) {
        printf("Test error: %s\n", err);
        return;
    }
    // age already given validated in test assumption
    char *out = process_user_data(name, age, nums, count);
    if (!out) {
        printf("Test error: processing failed.\n");
        return;
    }
    printf("%s\n", out);
    free(out);
}

int main(void) {
    // 5 test cases
    {
        int nums[] = {1,2,3,4,5};
        run_test("Alice", 29, nums, sizeof(nums)/sizeof(nums[0]), "Test Case 1");
    }
    {
        int nums[] = {-10,0,10,10};
        run_test("Bob O'Neil", 0, nums, sizeof(nums)/sizeof(nums[0]), "Test Case 2");
    }
    {
        int nums[] = {1000000, -1000000};
        run_test("Charles-John", 120, nums, sizeof(nums)/sizeof(nums[0]), "Test Case 3");
    }
    {
        int nums[] = {2,2,2,3,3,4};
        run_test("  Mary   Jane  ", 45, nums, sizeof(nums)/sizeof(nums[0]), "Test Case 4");
    }
    {
        int nums[] = {7,7,7,7,7};
        run_test("D'Artagnan", 35, nums, sizeof(nums)/sizeof(nums[0]), "Test Case 5");
    }

    // Interactive
    char name_in[INPUT_MAX_LEN + 2];
    char age_in[INPUT_MAX_LEN + 2];
    char nums_in[INPUT_MAX_LEN + 2];
    char name[NAME_MAX_LEN + 1];
    char err[128];
    int age = 0;
    int numbers[NUM_COUNT_MAX];
    size_t count = 0;

    printf("Enter name (letters, spaces, hyphen, apostrophe; 1-50 chars):\n");
    int rc = safe_readline(name_in, sizeof(name_in));
    if (rc != 0) {
        printf("Input error: invalid name input.\n");
        return 0;
    }
    if (validate_name(name_in, name, sizeof(name), err, sizeof(err)) != 0) {
        printf("Input error: %s\n", err);
        return 0;
    }

    printf("Enter age (0-120):\n");
    rc = safe_readline(age_in, sizeof(age_in));
    if (rc != 0) {
        printf("Input error: invalid age input.\n");
        return 0;
    }
    if (validate_age(age_in, &age, err, sizeof(err)) != 0) {
        printf("Input error: %s\n", err);
        return 0;
    }

    printf("Enter up to 100 integers between -1000000 and 1000000, separated by spaces or commas:\n");
    rc = safe_readline(nums_in, sizeof(nums_in));
    if (rc != 0) {
        printf("Input error: invalid numbers input.\n");
        return 0;
    }
    if (parse_numbers(nums_in, numbers, &count, err, sizeof(err)) != 0) {
        printf("Input error: %s\n", err);
        return 0;
    }

    char *out = process_user_data(name, age, numbers, count);
    if (!out) {
        printf("Processing error.\n");
        return 0;
    }
    printf("%s\n", out);
    free(out);
    return 0;
}