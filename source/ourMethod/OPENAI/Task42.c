#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/crypto.h>

#define SALT_LEN 16
#define KEY_LEN 32
#define ITERATIONS 210000
#define PASSWORD_MAX_AGE_SECONDS (90L * 24L * 60L * 60L)
#define MAX_USERS 100
#define USERNAME_MAX 32

typedef struct {
    char username[USERNAME_MAX + 1];
    unsigned char salt[SALT_LEN];
    unsigned char hash[KEY_LEN];
    int iterations;
    time_t created_at;
    int in_use;
} UserRecord;

typedef struct {
    UserRecord users[MAX_USERS];
} AuthSystem;

static int validate_username(const char* username) {
    if (!username) return 0;
    size_t len = strlen(username);
    if (len < 1 || len > USERNAME_MAX) return 0;
    for (size_t i = 0; i < len; i++) {
        char c = username[i];
        if (!(isalnum((unsigned char)c) || c == '_')) return 0;
    }
    return 1;
}

static int validate_password_policy(const char* password) {
    if (!password) return 0;
    size_t len = strlen(password);
    if (len < 12) return 0;
    int hasLower = 0, hasUpper = 0, hasDigit = 0, hasSpecial = 0;
    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)password[i];
        if (islower(c)) hasLower = 1;
        else if (isupper(c)) hasUpper = 1;
        else if (isdigit(c)) hasDigit = 1;
        else if (c >= 33 && c <= 126) hasSpecial = 1;
    }
    return hasLower && hasUpper && hasDigit && hasSpecial;
}

static int pbkdf2_derive(const char* password, const unsigned char* salt, int salt_len,
                         int iterations, int dklen, unsigned char* out_key) {
    const EVP_MD* md = EVP_sha256();
    if (!md) return 0;
    int rc = PKCS5_PBKDF2_HMAC(password, (int)strlen(password), salt, salt_len, iterations, md, dklen, out_key);
    return rc == 1;
}

static int find_user_index(AuthSystem* sys, const char* username) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (sys->users[i].in_use && strncmp(sys->users[i].username, username, USERNAME_MAX) == 0) {
            return i;
        }
    }
    return -1;
}

static int insert_user(AuthSystem* sys, const UserRecord* rec) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (!sys->users[i].in_use) {
            sys->users[i] = *rec;
            sys->users[i].in_use = 1;
            return 1;
        }
    }
    return 0;
}

int register_user(AuthSystem* sys, const char* username, const char* password) {
    if (!validate_username(username)) return 0;
    if (!validate_password_policy(password)) return 0;
    if (find_user_index(sys, username) >= 0) return 0;

    UserRecord rec;
    memset(&rec, 0, sizeof(rec));
    strncpy(rec.username, username, USERNAME_MAX);
    rec.username[USERNAME_MAX] = '\0';
    rec.iterations = ITERATIONS;
    rec.created_at = time(NULL);

    if (RAND_bytes(rec.salt, SALT_LEN) != 1) return 0;

    if (!pbkdf2_derive(password, rec.salt, SALT_LEN, rec.iterations, KEY_LEN, rec.hash)) {
        return 0;
    }
    rec.in_use = 1;
    return insert_user(sys, &rec);
}

// Returns: 0=success, 1=invalid credentials, 2=password expired
int authenticate(AuthSystem* sys, const char* username, const char* password) {
    int idx = find_user_index(sys, username);
    if (idx < 0) return 1;
    UserRecord* rec = &sys->users[idx];

    unsigned char derived[KEY_LEN];
    if (!pbkdf2_derive(password, rec->salt, SALT_LEN, rec->iterations, KEY_LEN, derived)) {
        return 1;
    }
    if (CRYPTO_memcmp(derived, rec->hash, KEY_LEN) != 0) {
        memset(derived, 0, sizeof(derived));
        return 1;
    }
    memset(derived, 0, sizeof(derived));

    time_t now = time(NULL);
    if ((now - rec->created_at) > PASSWORD_MAX_AGE_SECONDS) {
        return 2;
    }
    return 0;
}

int update_password(AuthSystem* sys, const char* username, const char* new_password) {
    if (!validate_password_policy(new_password)) return 0;
    int idx = find_user_index(sys, username);
    if (idx < 0) return 0;
    UserRecord* rec = &sys->users[idx];

    if (RAND_bytes(rec->salt, SALT_LEN) != 1) return 0;
    if (!pbkdf2_derive(new_password, rec->salt, SALT_LEN, ITERATIONS, KEY_LEN, rec->hash)) {
        return 0;
    }
    rec->iterations = ITERATIONS;
    rec->created_at = time(NULL);
    return 1;
}

// Test helper
int force_expire_user(AuthSystem* sys, const char* username, long seconds_ago) {
    int idx = find_user_index(sys, username);
    if (idx < 0) return 0;
    time_t now = time(NULL);
    sys->users[idx].created_at = now - (seconds_ago < 0 ? -seconds_ago : seconds_ago);
    return 1;
}

int main(void) {
    AuthSystem sys;
    memset(&sys, 0, sizeof(sys));

    int r1 = register_user(&sys, "alice", "Str0ng!Passw0rd");
    int a1 = authenticate(&sys, "alice", "Str0ng!Passw0rd");
    printf("Test1 register=%d auth=%d\n", r1, a1);

    int r2 = register_user(&sys, "bob", "password");
    printf("Test2 registerWeak=%d\n", r2);

    int r3 = register_user(&sys, "carol", "C0mpl3x#Pass123");
    int a3 = authenticate(&sys, "carol", "wrongPASS!");
    printf("Test3 register=%d authWrong=%d\n", r3, a3);

    int r4 = register_user(&sys, "dave", "Secur3!Passw0rd");
    int f4 = force_expire_user(&sys, "dave", 200L * 24L * 60L * 60L);
    int a4 = authenticate(&sys, "dave", "Secur3!Passw0rd");
    printf("Test4 register=%d forced=%d authExpired=%d\n", r4, f4, a4);

    int r5 = register_user(&sys, "erin", "Init!Passw0rd1");
    int u5 = update_password(&sys, "erin", "New!Passw0rd2");
    int a5_new = authenticate(&sys, "erin", "New!Passw0rd2");
    int a5_old = authenticate(&sys, "erin", "Init!Passw0rd1");
    printf("Test5 register=%d update=%d authNew=%d authOld=%d\n", r5, u5, a5_new, a5_old);

    return 0;
}