#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdint.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/crypto.h>

#define SALT_LEN 16
#define HASH_LEN 32
#define PBKDF2_ITER 210000
#define OTP_TTL_SECONDS 300

typedef struct User {
    char* username;
    unsigned char passwordSalt[SALT_LEN];
    unsigned char passwordHash[HASH_LEN];
    int iterations;
    unsigned char otpSalt[SALT_LEN];
    unsigned char otpHash[HASH_LEN];
    int hasOtp;
    time_t otpExpiry;
    struct User* next;
} User;

static User* USERS = NULL;

static int isValidUsername(const char* u) {
    size_t len = strlen(u);
    if (len < 3 || len > 64) return 0;
    for (size_t i = 0; i < len; i++) {
        char c = u[i];
        if (!(isalnum((unsigned char)c) || c == '.' || c == '_' || c == '-')) return 0;
    }
    return 1;
}

static int isStrongPassword(const char* p) {
    size_t len = strlen(p);
    if (len < 12 || len > 1024) return 0;
    int hasU=0, hasL=0, hasD=0, hasS=0;
    for (size_t i = 0; i < len; i++) {
        char c = p[i];
        if (isupper((unsigned char)c)) hasU = 1;
        else if (islower((unsigned char)c)) hasL = 1;
        else if (isdigit((unsigned char)c)) hasD = 1;
        else hasS = 1;
    }
    return hasU && hasL && hasD && hasS;
}

static User* findUser(const char* username) {
    User* cur = USERS;
    while (cur) {
        if (strcmp(cur->username, username) == 0) return cur;
        cur = cur->next;
    }
    return NULL;
}

static int pbkdf2(const unsigned char* pass, size_t passLen, const unsigned char* salt, size_t saltLen, int iter, unsigned char* out, size_t outLen) {
    return PKCS5_PBKDF2_HMAC((const char*)pass, (int)passLen, salt, (int)saltLen, iter, EVP_sha256(), (int)outLen, out) == 1;
}

static int constantTimeEq(const unsigned char* a, const unsigned char* b, size_t len) {
    return CRYPTO_memcmp(a, b, len) == 0;
}

static int generateNumericOtp(char* out, size_t outLen, int digits) {
    if (digits <= 0 || digits > 9) digits = 6;
    if (outLen < (size_t)digits + 1) return 0;
    uint32_t bound = 1;
    for (int i = 0; i < digits; i++) bound *= 10u;
    uint64_t limit = ((uint64_t)UINT32_MAX + 1u) / bound * bound;
    uint32_t val = 0;
    while (1) {
        if (RAND_bytes((unsigned char*)&val, sizeof(val)) != 1) continue;
        if ((uint64_t)val < limit) break;
    }
    uint32_t num = val % bound;
    snprintf(out, outLen, "%0*u", digits, num);
    return 1;
}

int registerUser(const char* username, const char* password) {
    if (!username || !password) return 0;
    if (!isValidUsername(username)) return 0;
    if (!isStrongPassword(password)) return 0;
    if (findUser(username) != NULL) return 0;

    User* u = (User*)calloc(1, sizeof(User));
    if (!u) return 0;
    u->username = strdup(username);
    if (!u->username) { free(u); return 0; }
    if (RAND_bytes(u->passwordSalt, SALT_LEN) != 1) { free(u->username); free(u); return 0; }
    if (!pbkdf2((const unsigned char*)password, strlen(password), u->passwordSalt, SALT_LEN, PBKDF2_ITER, u->passwordHash, HASH_LEN)) {
        free(u->username); free(u); return 0;
    }
    u->iterations = PBKDF2_ITER;
    u->hasOtp = 0;
    u->otpExpiry = 0;
    u->next = USERS;
    USERS = u;
    return 1;
}

typedef struct {
    int success;
    // For testing only; do not print in production
    char otp[16];
} LoginResult;

LoginResult startLogin(const char* username, const char* password) {
    LoginResult res;
    res.success = 0;
    res.otp[0] = '\0';
    User* u = findUser(username);
    if (!u) return res;

    unsigned char cand[HASH_LEN];
    if (!pbkdf2((const unsigned char*)password, strlen(password), u->passwordSalt, SALT_LEN, u->iterations, cand, HASH_LEN)) {
        return res;
    }
    if (!constantTimeEq(cand, u->passwordHash, HASH_LEN)) {
        return res;
    }

    char otp[16];
    if (!generateNumericOtp(otp, sizeof(otp), 6)) {
        return res;
    }
    if (RAND_bytes(u->otpSalt, SALT_LEN) != 1) {
        return res;
    }
    if (!pbkdf2((const unsigned char*)otp, strlen(otp), u->otpSalt, SALT_LEN, PBKDF2_ITER, u->otpHash, HASH_LEN)) {
        return res;
    }
    u->otpExpiry = time(NULL) + OTP_TTL_SECONDS;
    u->hasOtp = 1;
    res.success = 1;
    snprintf(res.otp, sizeof(res.otp), "%s", otp);
    return res;
}

int verifyOtp(const char* username, const char* otp) {
    User* u = findUser(username);
    if (!u) return 0;
    if (!u->hasOtp) return 0;
    time_t now = time(NULL);
    if (now > u->otpExpiry) return 0;

    unsigned char cand[HASH_LEN];
    if (!pbkdf2((const unsigned char*)otp, strlen(otp), u->otpSalt, SALT_LEN, PBKDF2_ITER, cand, HASH_LEN)) {
        return 0;
    }
    int ok = constantTimeEq(cand, u->otpHash, HASH_LEN);
    if (ok) {
        u->hasOtp = 0;
        u->otpExpiry = 0;
        memset(u->otpHash, 0, HASH_LEN);
        memset(u->otpSalt, 0, SALT_LEN);
    }
    return ok;
}

// Testing helper
void expireOtpForTest(const char* username) {
    User* u = findUser(username);
    if (u) {
        u->otpExpiry = time(NULL) - 1;
    }
}

int main(void) {
    // Test 1: Successful registration and 2FA login
    int reg1 = registerUser("alice", "Str0ng!Passw0rd");
    LoginResult lr1 = startLogin("alice", "Str0ng!Passw0rd");
    int v1 = lr1.success && verifyOtp("alice", lr1.otp);
    printf("Test1 (success 2FA): %s\n", (reg1 && v1) ? "1" : "0");

    // Test 2: Wrong password
    LoginResult lr2 = startLogin("alice", "wrongPassword1!");
    printf("Test2 (wrong password): %s\n", (!lr2.success) ? "1" : "0");

    // Test 3: Wrong OTP
    LoginResult lr3 = startLogin("alice", "Str0ng!Passw0rd");
    int v3 = lr3.success && verifyOtp("alice", "000000");
    printf("Test3 (wrong OTP): %s\n", (!v3) ? "1" : "0");

    // Test 4: Expired OTP
    LoginResult lr4 = startLogin("alice", "Str0ng!Passw0rd");
    expireOtpForTest("alice");
    int v4 = lr4.success && verifyOtp("alice", lr4.otp);
    printf("Test4 (expired OTP): %s\n", (!v4) ? "1" : "0");

    // Test 5: Another user end-to-end
    int reg2 = registerUser("bob_user", "An0ther$trongPass");
    LoginResult lr5 = startLogin("bob_user", "An0ther$trongPass");
    int v5 = lr5.success && verifyOtp("bob_user", lr5.otp);
    printf("Test5 (second user success): %s\n", (reg2 && v5) ? "1" : "0");

    return 0;
}