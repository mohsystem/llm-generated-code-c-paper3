#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

static bool is_ascii_letter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}
static bool is_ascii_digit(char c) {
    return (c >= '0' && c <= '9');
}
static bool is_allowed_local_char(char c) {
    if (is_ascii_letter(c) || is_ascii_digit(c)) return true;
    switch (c) {
        case '!': case '#': case '$': case '%': case '&': case '\'': case '*':
        case '+': case '-': case '/': case '=': case '?': case '^': case '_':
        case '`': case '{': case '|': case '}': case '~': case '.':
            return true;
        default:
            return false;
    }
}
static bool is_allowed_domain_char(char c) {
    return is_ascii_letter(c) || is_ascii_digit(c) || c == '-' || c == '.';
}

bool is_valid_email(const char* email) {
    if (email == NULL) return false;

    size_t len = strlen(email);
    if (len < 3 || len > 254) return false;

    // No leading/trailing whitespace and ASCII only printable
    if (email[0] == ' ' || email[len - 1] == ' ') return false;
    for (size_t i = 0; i < len; i++) {
        unsigned char uc = (unsigned char)email[i];
        if (uc <= 0x1F || uc >= 0x7F) return false;
    }

    // Find '@'
    const char* at_ptr = strchr(email, '@');
    if (at_ptr == NULL) return false;
    if (strchr(at_ptr + 1, '@') != NULL) return false; // multiple '@'
    size_t at_index = (size_t)(at_ptr - email);
    if (at_index == 0 || at_index == len - 1) return false;

    size_t local_len = at_index;
    size_t domain_len = len - at_index - 1;

    if (local_len < 1 || local_len > 64) return false;
    if (domain_len < 1 || domain_len > 253) return false;

    // Validate local part
    if (email[0] == '.' || email[local_len - 1] == '.') return false;
    bool prev_dot = false;
    for (size_t i = 0; i < local_len; i++) {
        char c = email[i];
        if (!is_allowed_local_char(c)) return false;
        if (c == '.') {
            if (prev_dot) return false;
            prev_dot = true;
        } else {
            prev_dot = false;
        }
    }

    // Validate domain part
    const char* domain = email + at_index + 1;
    if (domain[0] == '.' || domain[domain_len - 1] == '.') return false;

    bool has_dot = false;
    size_t label_len = 0;
    bool current_label_alpha_only = true;
    bool last_label_alpha_only = false;
    char prev = 0;

    for (size_t i = 0; i < domain_len; i++) {
        char c = domain[i];

        if (c == '.') {
            if (label_len == 0) return false; // empty label or consecutive dots
            if (prev == '-') return false;    // label cannot end with hyphen
            has_dot = true;
            last_label_alpha_only = current_label_alpha_only;
            label_len = 0;
            current_label_alpha_only = true;
            prev = c;
            continue;
        }

        if (!is_allowed_domain_char(c)) return false;

        if (c == '-') {
            if (label_len == 0) return false; // label cannot start with hyphen
            current_label_alpha_only = false;
        } else if (is_ascii_digit(c)) {
            current_label_alpha_only = false;
        } else if (is_ascii_letter(c)) {
            // ok
        } else {
            return false;
        }

        label_len++;
        if (label_len > 63) return false;
        prev = c;
    }

    if (label_len == 0) return false;
    if (prev == '-') return false;
    last_label_alpha_only = current_label_alpha_only;

    if (!has_dot) return false;
    if (!last_label_alpha_only || label_len < 2) return false;

    return true;
}

int main(void) {
    const char* tests[5] = {
        "alice@example.com",
        "john.doe+tag@sub.example.co.uk",
        ".startsWithDot@domain.com",
        "no_at_symbol.domain.com",
        "bad-domain@exa_mple.com"
    };
    for (int i = 0; i < 5; i++) {
        printf("%s => %s\n", tests[i], is_valid_email(tests[i]) ? "true" : "false");
    }
    return 0;
}