#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/hmac.h>
#include <openssl/rand.h>
#include <openssl/crypto.h>

static const unsigned char MAGIC[4] = { 'T', 'K', 'N', '1' };
static const unsigned char VERSION = 1;
#define NONCE_LEN 16
#define TAG_LEN 32
#define MAX_USER_LEN 1024
#define MIN_KEY_LEN 16
#define MIN_TTL 1
#define MAX_TTL 604800

static void append_u64_be(unsigned char* buf, size_t* off, unsigned long long v) {
    for (int i = 7; i >= 0; --i) buf[(*off)++] = (unsigned char)((v >> (i*8)) & 0xFF);
}
static void append_u32_be(unsigned char* buf, size_t* off, unsigned int v) {
    for (int i = 3; i >= 0; --i) buf[(*off)++] = (unsigned char)((v >> (i*8)) & 0xFF);
}
static void append_u16_be(unsigned char* buf, size_t* off, unsigned short v) {
    buf[(*off)++] = (unsigned char)((v >> 8) & 0xFF);
    buf[(*off)++] = (unsigned char)(v & 0xFF);
}

static char* b64url_encode(const unsigned char* data, size_t len) {
    static const char* b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    size_t out_len = ((len + 2) / 3) * 4;
    char* tmp = (char*)malloc(out_len + 1);
    if (!tmp) return NULL;
    size_t i = 0, j = 0;
    while (i + 3 <= len) {
        unsigned int n = (data[i] << 16) | (data[i+1] << 8) | data[i+2];
        tmp[j++] = b64[(n >> 18) & 63];
        tmp[j++] = b64[(n >> 12) & 63];
        tmp[j++] = b64[(n >> 6) & 63];
        tmp[j++] = b64[n & 63];
        i += 3;
    }
    if (i + 1 == len) {
        unsigned int n = (data[i] << 16);
        tmp[j++] = b64[(n >> 18) & 63];
        tmp[j++] = b64[(n >> 12) & 63];
        tmp[j++] = '=';
        tmp[j++] = '=';
    } else if (i + 2 == len) {
        unsigned int n = (data[i] << 16) | (data[i+1] << 8);
        tmp[j++] = b64[(n >> 18) & 63];
        tmp[j++] = b64[(n >> 12) & 63];
        tmp[j++] = b64[(n >> 6) & 63];
        tmp[j++] = '=';
    }
    tmp[j] = '\0';
    for (size_t k = 0; k < j; ++k) {
        if (tmp[k] == '+') tmp[k] = '-';
        else if (tmp[k] == '/') tmp[k] = '_';
    }
    // remove padding '='
    while (j > 0 && tmp[j-1] == '=') j--;
    tmp[j] = '\0';
    return tmp;
}

static int b64url_decode(const char* in, unsigned char** out, size_t* out_len) {
    if (!in || !out || !out_len) return 0;
    size_t len = strlen(in);
    char* s = (char*)malloc(len + 5);
    if (!s) return 0;
    for (size_t i = 0; i < len; ++i) {
        if (in[i] == '-') s[i] = '+';
        else if (in[i] == '_') s[i] = '/';
        else s[i] = in[i];
    }
    size_t pad = (4 - (len % 4)) % 4;
    for (size_t i = 0; i < pad; ++i) s[len + i] = '=';
    s[len + pad] = '\0';
    len = len + pad;

    int val_table[256];
    for (int i = 0; i < 256; ++i) val_table[i] = -2;
    for (int i = 'A'; i <= 'Z'; ++i) val_table[i] = i - 'A';
    for (int i = 'a'; i <= 'z'; ++i) val_table[i] = i - 'a' + 26;
    for (int i = '0'; i <= '9'; ++i) val_table[i] = i - '0' + 52;
    val_table[(int)'+'] = 62;
    val_table[(int)'/'] = 63;
    val_table[(int)'='] = -1;

    unsigned char* dec = (unsigned char*)malloc((len / 4) * 3);
    if (!dec) { free(s); return 0; }
    size_t j = 0;
    for (size_t i = 0; i < len; i += 4) {
        int v0 = val_table[(unsigned char)s[i]];
        int v1 = val_table[(unsigned char)s[i+1]];
        int v2 = val_table[(unsigned char)s[i+2]];
        int v3 = val_table[(unsigned char)s[i+3]];
        if (v0 < 0 || v1 < 0 || v2 < -1 || v3 < -1) { free(dec); free(s); return 0; }
        unsigned int triple = ((unsigned int)v0 << 18) | ((unsigned int)v1 << 12) | (((v2 < 0)?0:(unsigned int)v2) << 6) | ((v3 < 0)?0:(unsigned int)v3);
        dec[j++] = (triple >> 16) & 0xFF;
        if (v2 >= 0) dec[j++] = (triple >> 8) & 0xFF;
        if (v3 >= 0) dec[j++] = triple & 0xFF;
        if (v2 < 0) { if (j < 2) { free(dec); free(s); return 0; } j -= 2; }
        else if (v3 < 0) { if (j < 1) { free(dec); free(s); return 0; } j -= 1; }
    }
    free(s);
    *out = dec;
    *out_len = j;
    return 1;
}

static int hmac_sha256(const unsigned char* key, size_t key_len, const unsigned char* data, size_t data_len, unsigned char out[TAG_LEN]) {
    unsigned int len = 0;
    unsigned char* res = HMAC(EVP_sha256(), key, (int)key_len, data, data_len, out, &len);
    return res != NULL && len == TAG_LEN;
}

static char* generate_token(const char* user_id, const unsigned char* key, size_t key_len, int ttl_seconds) {
    if (!user_id || !key) return NULL;
    size_t user_len = strlen(user_id);
    if (user_len == 0 || user_len > MAX_USER_LEN) return NULL;
    if (key_len < MIN_KEY_LEN) return NULL;
    if (ttl_seconds < MIN_TTL || ttl_seconds > MAX_TTL) return NULL;

    unsigned char nonce[NONCE_LEN];
    if (RAND_bytes(nonce, NONCE_LEN) != 1) return NULL;

    unsigned long long now = (unsigned long long)time(NULL);

    size_t msg_len = 4 + 1 + 8 + 4 + NONCE_LEN + 2 + user_len;
    unsigned char* msg = (unsigned char*)malloc(msg_len + TAG_LEN);
    if (!msg) return NULL;

    size_t off = 0;
    memcpy(msg + off, MAGIC, 4); off += 4;
    msg[off++] = VERSION;
    append_u64_be(msg, &off, now);
    append_u32_be(msg, &off, (unsigned int)ttl_seconds);
    memcpy(msg + off, nonce, NONCE_LEN); off += NONCE_LEN;
    append_u16_be(msg, &off, (unsigned short)user_len);
    memcpy(msg + off, user_id, user_len); off += user_len;

    unsigned char tag[TAG_LEN];
    if (!hmac_sha256(key, key_len, msg, msg_len, tag)) {
        free(msg);
        return NULL;
    }
    memcpy(msg + msg_len, tag, TAG_LEN);

    char* token = b64url_encode(msg, msg_len + TAG_LEN);
    free(msg);
    return token;
}

static int verify_token(const char* token, const unsigned char* key, size_t key_len, const char* expected_user, long long now_epoch) {
    if (!token || !key || !expected_user) return 0;
    if (key_len < MIN_KEY_LEN) return 0;

    unsigned char* raw = NULL;
    size_t raw_len = 0;
    if (!b64url_decode(token, &raw, &raw_len)) return 0;

    size_t min_len = 4 + 1 + 8 + 4 + NONCE_LEN + 2 + TAG_LEN;
    if (raw_len < min_len) { free(raw); return 0; }

    size_t off = 0;
    if (memcmp(raw + off, MAGIC, 4) != 0) { free(raw); return 0; }
    off += 4;
    unsigned char ver = raw[off++]; if (ver != VERSION) { free(raw); return 0; }

    if (off + 8 + 4 + NONCE_LEN + 2 > raw_len - TAG_LEN) { free(raw); return 0; }

    unsigned long long ts = 0;
    for (int i = 0; i < 8; ++i) ts = (ts << 8) | raw[off++];
    unsigned int ttl = 0;
    for (int i = 0; i < 4; ++i) ttl = (ttl << 8) | raw[off++];
    if (ttl < MIN_TTL || ttl > MAX_TTL) { free(raw); return 0; }

    off += NONCE_LEN;

    unsigned short user_len = (unsigned short)((raw[off] << 8) | raw[off+1]); off += 2;
    if (user_len < 1 || user_len > MAX_USER_LEN) { free(raw); return 0; }
    if (off + user_len != raw_len - TAG_LEN) { free(raw); return 0; }

    const unsigned char* user_ptr = raw + off;
    off += user_len;

    const unsigned char* tag = raw + off;

    unsigned char exp_tag[TAG_LEN];
    if (!hmac_sha256(key, key_len, raw, raw_len - TAG_LEN, exp_tag)) { free(raw); return 0; }
    if (CRYPTO_memcmp(tag, exp_tag, TAG_LEN) != 0) { free(raw); return 0; }

    size_t expected_len = strlen(expected_user);
    if (expected_len != user_len || CRYPTO_memcmp(user_ptr, expected_user, user_len) != 0) { free(raw); return 0; }

    long long now = (now_epoch > 0) ? now_epoch : (long long)time(NULL);
    if (now > (long long)(ts + ttl)) { free(raw); return 0; }

    free(raw);
    return 1;
}

static char* tamper_token(const char* token) {
    if (!token) return NULL;
    size_t len = strlen(token);
    if (len == 0) {
        char* out = (char*)malloc(1); if (out) out[0] = '\0'; return out;
    }
    char* out = (char*)malloc(len + 1);
    if (!out) return NULL;
    memcpy(out, token, len + 1);
    const char* alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
    char last = out[len - 1];
    const char* p = strchr(alpha, last);
    if (!p) {
        out[len - 1] = alpha[0];
    } else {
        out[len - 1] = (last == alpha[0]) ? alpha[1] : alpha[0];
    }
    return out;
}

int main(void) {
    unsigned char key[32];
    if (RAND_bytes(key, sizeof(key)) != 1) {
        printf("RNG failure\n");
        return 1;
    }
    const char* users[5] = {"alice", "bob", "carol", "dave_123", "eve@example.com"};

    // Test 1: valid
    char* t1 = generate_token(users[0], key, sizeof(key), 600);
    int r1 = t1 ? verify_token(t1, key, sizeof(key), users[0], (long long)time(NULL)) : 0;
    printf("Test1 valid: %s\n", r1 ? "true" : "false");
    free(t1);

    // Test 2: expired
    char* t2 = generate_token(users[1], key, sizeof(key), 1);
    int r2 = t2 ? verify_token(t2, key, sizeof(key), users[1], (long long)time(NULL) + 5000) : 0;
    printf("Test2 expired: %s\n", (!r2) ? "true" : "false");
    free(t2);

    // Test 3: wrong user
    char* t3 = generate_token(users[2], key, sizeof(key), 600);
    int r3 = t3 ? verify_token(t3, key, sizeof(key), users[0], (long long)time(NULL)) : 0;
    printf("Test3 wrong user: %s\n", (!r3) ? "true" : "false");
    free(t3);

    // Test 4: tampered
    char* t4 = generate_token(users[3], key, sizeof(key), 600);
    char* t4bad = tamper_token(t4 ? t4 : "");
    int r4 = t4bad ? verify_token(t4bad, key, sizeof(key), users[3], (long long)time(NULL)) : 0;
    printf("Test4 tampered: %s\n", (!r4) ? "true" : "false");
    free(t4);
    free(t4bad);

    // Test 5: wrong key
    unsigned char wrongKey[32];
    RAND_bytes(wrongKey, sizeof(wrongKey));
    char* t5 = generate_token(users[4], key, sizeof(key), 600);
    int r5 = t5 ? verify_token(t5, wrongKey, sizeof(wrongKey), users[4], (long long)time(NULL)) : 0;
    printf("Test5 wrong key: %s\n", (!r5) ? "true" : "false");
    free(t5);

    return 0;
}