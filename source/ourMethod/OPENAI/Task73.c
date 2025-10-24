#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

static bool has_sequential_run(const char *s) {
    size_t n = strlen(s);
    if (n < 3) return false;
    for (size_t i = 2; i < n; ++i) {
        unsigned char a = (unsigned char) s[i - 2];
        unsigned char b = (unsigned char) s[i - 1];
        unsigned char c = (unsigned char) s[i];
        if (isalpha(a) && isalpha(b) && isalpha(c)) {
            int x = tolower(a), y = tolower(b), z = tolower(c);
            if ((y == x + 1 && z == y + 1) || (y == x - 1 && z == y - 1)) return true;
        } else if (isdigit(a) && isdigit(b) && isdigit(c)) {
            int x = a, y = b, z = c;
            if ((y == x + 1 && z == y + 1) || (y == x - 1 && z == y - 1)) return true;
        }
    }
    return false;
}

bool is_valid_admin_password(const char *password) {
    if (password == NULL) return false;

    const int minLen = 12;
    const int maxLen = 128;
    size_t len = strlen(password);
    if (len < (size_t)minLen || len > (size_t)maxLen) return false;

    // Printable ASCII only (no spaces, no control)
    for (size_t i = 0; i < len; ++i) {
        unsigned char ch = (unsigned char) password[i];
        if (ch < 33 || ch > 126) return false;
    }

    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    int repeatRun = 1;
    for (size_t i = 0; i < len; ++i) {
        unsigned char ch = (unsigned char) password[i];
        if (isupper(ch)) hasUpper = true;
        else if (islower(ch)) hasLower = true;
        else if (isdigit(ch)) hasDigit = true;
        else hasSpecial = true;

        if (i > 0) {
            if (password[i] == password[i - 1]) {
                repeatRun++;
                if (repeatRun >= 3) return false;
            } else {
                repeatRun = 1;
            }
        }
    }
    if (!(hasUpper && hasLower && hasDigit && hasSpecial)) return false;

    // Lowercase copy for checks
    char lower[129];
    if (len >= sizeof(lower)) return false; // defensive, though we already bounded len
    for (size_t i = 0; i < len; ++i) {
        lower[i] = (char) tolower((unsigned char) password[i]);
    }
    lower[len] = '\0';

    if (strstr(lower, "admin") != NULL) return false;
    if (strstr(lower, "password") != NULL || strstr(lower, "qwerty") != NULL) return false;

    const char *banned[] = {
        "admin", "admin123", "admin@123", "administrator",
        "password", "passw0rd", "p@ssw0rd", "p4ssw0rd",
        "qwerty", "qwerty123", "letmein", "welcome",
        "123456", "123456789", "iloveyou", "12345678"
    };
    size_t banned_count = sizeof(banned) / sizeof(banned[0]);
    for (size_t i = 0; i < banned_count; ++i) {
        if (strcmp(lower, banned[i]) == 0) return false;
    }

    if (has_sequential_run(password)) return false;

    return true;
}

int main(void) {
    const char *tests[5] = {
        "Admin@123",       // invalid
        "S3cure#Admin!",   // invalid
        "G00d#Pa55word!",  // valid
        "aaaaaaaaaaaa",    // invalid
        "N0t$0Obv10us!"    // valid
    };
    for (int i = 0; i < 5; ++i) {
        bool res = is_valid_admin_password(tests[i]);
        printf("Test %d: %s\n", i + 1, res ? "true" : "false");
    }
    return 0;
}