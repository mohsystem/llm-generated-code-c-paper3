#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define USERNAME_MAX 32
#define NAME_MAX 64
#define EMAIL_MAX 64
#define PHONE_MAX 32
#define ISO_MAX 32

typedef struct {
    char username[USERNAME_MAX + 1];
    char fullName[NAME_MAX + 1];
    char email[EMAIL_MAX + 1];
    char phone[PHONE_MAX + 1];
    char createdAtIso[ISO_MAX + 1];
} Customer;

typedef struct {
    int found;      // 1 if found, 0 otherwise
    Customer value; // valid only if found == 1
} Result;

static bool is_valid_char(unsigned char c) {
    if ((c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z') ||
        (c >= '0' && c <= '9') ||
        c == '_' || c == '-' || c == '.') {
        return true;
    }
    return false;
}

static bool is_valid_username(const char* username) {
    if (username == NULL) return false;
    size_t len = strlen(username);
    if (len < 1 || len > USERNAME_MAX) return false;
    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)username[i];
        if (!is_valid_char(c)) return false;
    }
    return true;
}

static void safe_copy(char* dest, size_t destsz, const char* src) {
    if (destsz == 0) return;
    if (src == NULL) {
        dest[0] = '\0';
        return;
    }
    // Copy up to destsz - 1 and ensure null-termination
    snprintf(dest, destsz, "%s", src);
}

static void seed_in_memory_db(Customer* out, size_t* count) {
    static const Customer seed[] = {
        {"alice.smith", "Alice Smith", "alice@example.com", "+1-202-555-0101", "2024-07-01T10:00:00Z"},
        {"bob_1984", "Bob Stone", "bob1984@example.com", "+1-202-555-0102", "2023-12-11T08:45:30Z"},
        {"charlie", "Charlie Kim", "charlie@example.org", "+44-20-7946-0958", "2022-05-20T15:20:10Z"}
    };
    size_t n = sizeof(seed) / sizeof(seed[0]);
    for (size_t i = 0; i < n; i++) {
        out[i] = seed[i];
    }
    *count = n;
}

static Result get_customer_by_username(const Customer* table, size_t count, const char* username) {
    Result r;
    r.found = 0;
    memset(&r.value, 0, sizeof(r.value));

    if (!is_valid_username(username)) {
        return r;
    }
    for (size_t i = 0; i < count; i++) {
        if (strncmp(table[i].username, username, USERNAME_MAX) == 0 && table[i].username[0] != '\0') {
            r.found = 1;
            r.value = table[i];
            return r;
        }
    }
    return r;
}

static void json_escape_and_append(char* dst, size_t dstsz, const char* s) {
    size_t used = strnlen(dst, dstsz);
    if (used >= dstsz) return;
    if (s == NULL) s = "";
    // append opening quote
    if (used + 1 < dstsz) { dst[used++] = '"'; dst[used] = '\0'; }

    for (const unsigned char* p = (const unsigned char*)s; *p != '\0'; ++p) {
        char buf[8] = {0};
        const char* add = NULL;
        switch (*p) {
            case '\\': add = "\\"; break;
            case '\"': add = "\""; break;
            case '\b': add = "\\b";  break;
            case '\f': add = "\\f";  break;
            case '\n': add = "\\n";  break;
            case '\r': add = "\\r";  break;
            case '\t': add = "\\t";  break;
            default:
                if (*p < 0x20) {
                    snprintf(buf, sizeof(buf), "\\u%04x", *p);
                    add = buf;
                } else {
                    char cbuf[2] = {(char)*p, '\0'};
                    add = cbuf;
                }
        }
        size_t addlen = strlen(add);
        if (used + addlen >= dstsz) break;
        memcpy(dst + used, add, addlen);
        used += addlen;
        dst[used] = '\0';
    }
    // append closing quote
    if (used + 1 < dstsz) { dst[used++] = '"'; dst[used] = '\0'; }
}

static void result_to_json(const Result* r, const char* uname, char* out, size_t outsz) {
    if (outsz == 0) return;
    out[0] = '\0';
    if (!r->found) {
        snprintf(out, outsz, "{\"error\":\"Customer not found or invalid username\",\"username\":");
        json_escape_and_append(out, outsz, uname ? uname : "");
        size_t used = strnlen(out, outsz);
        if (used + 1 < outsz) { out[used++] = '}'; out[used] = '\0'; }
        return;
    }
    // Build JSON safely
    snprintf(out, outsz, "{");
    size_t used = strnlen(out, outsz);

    // "username"
    snprintf(out + used, (used < outsz ? outsz - used : 0), "\"username\":");
    used = strnlen(out, outsz);
    json_escape_and_append(out, outsz, r->value.username);
    used = strnlen(out, outsz);

    // "fullName"
    if (used + 1 < outsz) { out[used++] = ','; out[used] = '\0'; }
    snprintf(out + used, (used < outsz ? outsz - used : 0), "\"fullName\":");
    used = strnlen(out, outsz);
    json_escape_and_append(out, outsz, r->value.fullName);
    used = strnlen(out, outsz);

    // "email"
    if (used + 1 < outsz) { out[used++] = ','; out[used] = '\0'; }
    snprintf(out + used, (used < outsz ? outsz - used : 0), "\"email\":");
    used = strnlen(out, outsz);
    json_escape_and_append(out, outsz, r->value.email);
    used = strnlen(out, outsz);

    // "phone"
    if (used + 1 < outsz) { out[used++] = ','; out[used] = '\0'; }
    snprintf(out + used, (used < outsz ? outsz - used : 0), "\"phone\":");
    used = strnlen(out, outsz);
    json_escape_and_append(out, outsz, r->value.phone);
    used = strnlen(out, outsz);

    // "createdAtIso"
    if (used + 1 < outsz) { out[used++] = ','; out[used] = '\0'; }
    snprintf(out + used, (used < outsz ? outsz - used : 0), "\"createdAtIso\":");
    used = strnlen(out, outsz);
    json_escape_and_append(out, outsz, r->value.createdAtIso);
    used = strnlen(out, outsz);

    if (used + 1 < outsz) { out[used++] = '}'; out[used] = '\0'; }
}

int main(int argc, char* argv[]) {
    Customer db[8];
    size_t count = 0;
    seed_in_memory_db(db, &count);

    // If username provided via command line arg, query it
    if (argc > 1 && argv[1] != NULL) {
        Result r = get_customer_by_username(db, count, argv[1]);
        char json[512];
        result_to_json(&r, argv[1], json, sizeof json);
        puts(json);
    }

    // 5 test cases
    const char* tests[5] = {
        "alice.smith",                         // existing
        "bob_1984",                            // existing
        "invalid user",                        // invalid (space)
        "unknown_user",                        // not existing
        "averylongusername_exceeding_32_chars" // invalid (too long)
    };

    for (int i = 0; i < 5; i++) {
        Result r = get_customer_by_username(db, count, tests[i]);
        char json[512];
        result_to_json(&r, tests[i], json, sizeof json);
        puts(json);
    }

    return 0;
}