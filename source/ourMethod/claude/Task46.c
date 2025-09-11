
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <regex.h>
#include <stdbool.h>

#define MAX_NAME_LEN 51
#define MAX_EMAIL_LEN 255
#define MAX_PASSWORD_LEN 255
#define SALT_LEN 16
#define HASH_LEN SHA512_DIGEST_LENGTH*2 + 1

typedef struct {
    sqlite3 *db;
} Task46;

static bool validate_input(const char *name, const char *email, const char *password) {
    if (!name || !email || !password) {
        return false;
    }

    regex_t nameRegex, emailRegex, passwordRegex;
    int reti;
    bool valid = true;

    // Validate name - letters, numbers, spaces only, 2-50 chars
    reti = regcomp(&nameRegex, "^[a-zA-Z0-9[:space:]]{2,50}$", REG_EXTENDED);
    if (reti || regexec(&nameRegex, name, 0, NULL, 0) != 0) {
        valid = false;
    }
    regfree(&nameRegex);

    if (!valid) return false;

    // Validate email format
    reti = regcomp(&emailRegex, "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\\\.[A-Za-z]{2,}$", REG_EXTENDED);
    if (reti || regexec(&emailRegex, email, 0, NULL, 0) != 0) {
        valid = false;
    }
    regfree(&emailRegex);

    if (!valid) return false;

    // Validate password - min 8 chars, must contain digit, lower, upper, special char
    reti = regcomp(&passwordRegex, "^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=.*[@#$%^&+=])(?=\\\\S+$).{8,', type='text')