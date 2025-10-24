#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/**
 * A practical, non-regex based email validation function.
 * This function implements a reasonable subset of validation rules.
 * It is not fully RFC 5322 compliant but covers common formats safely.
 * @param email The null-terminated string to validate.
 * @return true if the email appears valid, false otherwise.
 */
bool isValidEmail(const char* email) {
    if (email == NULL) {
        return false;
    }

    size_t len = strlen(email);
    if (len < 6 || len > 254) { // Basic length checks
        return false;
    }

    // Find exactly one '@'
    const char* at_ptr = strchr(email, '@');
    if (at_ptr == NULL || strrchr(email, '@') != at_ptr) {
        return false;
    }

    size_t local_part_len = at_ptr - email;
    if (local_part_len == 0 || local_part_len > 64) { // Local part length
        return false;
    }

    const char* domain_part = at_ptr + 1;
    size_t domain_part_len = strlen(domain_part);
    if (domain_part_len == 0 || domain_part_len > 253) { // Domain part length
        return false;
    }

    // Check local part for invalid characters or sequences
    if (email[0] == '.' || email[local_part_len - 1] == '.') {
        return false; // Cannot start or end with a dot
    }
    for (size_t i = 0; i < local_part_len; ++i) {
        if (!(isalnum(email[i]) || email[i] == '.' || email[i] == '_' || email[i] == '%' || email[i] == '+' || email[i] == '-')) {
            return false;
        }
        if (i > 0 && email[i] == '.' && email[i - 1] == '.') {
            return false; // Consecutive dots not allowed
        }
    }

    // Check domain part
    if (domain_part[0] == '-' || domain_part[0] == '.' ||
        domain_part[domain_part_len - 1] == '-' || domain_part[domain_part_len - 1] == '.') {
        return false; // Cannot start or end with a hyphen or dot
    }

    const char* last_dot_ptr = strrchr(domain_part, '.');
    if (last_dot_ptr == NULL) {
        return false; // Domain must have at least one dot for TLD
    }

    for (size_t i = 0; i < domain_part_len; ++i) {
        if (!(isalnum(domain_part[i]) || domain_part[i] == '.' || domain_part[i] == '-')) {
            return false;
        }
        if (i > 0) {
            if ((domain_part[i] == '.' && domain_part[i - 1] == '.') ||
                (domain_part[i] == '-' && domain_part[i - 1] == '.') ||
                (domain_part[i] == '.' && domain_part[i - 1] == '-')) {
                return false; // Invalid combinations like '..', '.-', '-.'
            }
        }
    }
    
    // TLD must be at least 2 characters and all alphabetic
    size_t tld_len = strlen(last_dot_ptr + 1);
    if (tld_len < 2) {
        return false;
    }
    for (size_t i = 0; i < tld_len; ++i) {
        if (!isalpha((unsigned char)last_dot_ptr[i + 1])) {
            return false;
        }
    }

    return true;
}

int main() {
    const char* testEmails[] = {
        "test@example.com",        // valid
        "test.name@example.co.uk", // valid
        "test..name@example.com",  // invalid (consecutive dots)
        "test@example",            // invalid (no TLD)
        "@example.com"             // invalid (empty local part)
    };
    int num_tests = sizeof(testEmails) / sizeof(testEmails[0]);

    for (int i = 0; i < num_tests; i++) {
        printf("Email: %-25s is valid? %s\n", testEmails[i], isValidEmail(testEmails[i]) ? "true" : "false");
    }

    return 0;
}