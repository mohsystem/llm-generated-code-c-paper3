#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/crypto.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define SALT_LEN 16
#define HASH_LEN 32
#define PBKDF2_ITER 210000
#define SESSION_TTL 1800
#define PW_MAX_AGE (90*24*3600)
#define MAX_USERS 128
#define MAX_SESSIONS 256
#define TOKEN_LEN 64 /* hex length for 32 bytes */

typedef struct {
    char username[33];
    unsigned char salt[SALT_LEN];
    unsigned char hash[HASH_LEN];
    long created_at;
    int used;
} User;

typedef struct {
    char token[TOKEN_LEN+1];
    char username[33];
    long expires_at;
    int used;
} Session;

typedef struct {
    char method[8];
    char path[32];
    struct {
        char key[32];
        char value[256];
    } headers[8];
    int headers_count;
    struct {
        char key[32];
        char value[256];
    } body[8];
    int body_count;
} Request;

typedef struct {
    int status;
    struct {
        char key[32];
        char value[256];
    } headers[8];
    int headers_count;
    char body[256];
} Response;

typedef struct {
    User users[MAX_USERS];
    Session sessions[MAX_SESSIONS];
} SessionManager;

/* Utilities */
static long now_sec(void) {
    return time(NULL);
}

static void to_hex(const unsigned char* in, size_t len, char* out_hex, size_t out_hex_size) {
    static const char* hexd = "0123456789abcdef";
    size_t i;
    if (out_hex_size < len*2 + 1) return;
    for (i = 0; i < len; i++) {
        out_hex[i*2] = hexd[(in[i] >> 4) & 0xF];
        out_hex[i*2+1] = hexd[in[i] & 0xF];
    }
    out_hex[len*2] = '\0';
}

static int valid_username(const char* u) {
    size_t n;
    if (!u) return 0;
    n = strlen(u);
    if (n < 3 || n > 32) return 0;
    for (size_t i = 0; i < n; i++) {
        char c = u[i];
        if (!(isalnum((unsigned char)c) || c == '_' || c == '-')) return 0;
    }
    return 1;
}

static int strong_password(const char* p) {
    size_t n;
    int up=0, lo=0, di=0, sp=0;
    if (!p) return 0;
    n = strlen(p);
    if (n < 12 || n > 128) return 0;
    for (size_t i = 0; i < n; i++) {
        unsigned char c = (unsigned char)p[i];
        if (isupper(c)) up = 1;
        else if (islower(c)) lo = 1;
        else if (isdigit(c)) di = 1;
        else sp = 1;
    }
    return up && lo && di && sp;
}

static void safe_json(const char* in, char* out, size_t out_size) {
    size_t j = 0;
    for (size_t i = 0; in && in[i] && j+2 < out_size; i++) {
        char c = in[i];
        if (c == '\\' || c == '"') {
            if (j+2 >= out_size) break;
            out[j++] = '\\';
            out[j++] = c;
        } else {
            out[j++] = c;
        }
    }
    out[j] = '\0';
}

/* Session Manager functions */
static void mgr_init(SessionManager* m) {
    memset(m, 0, sizeof(*m));
}

static int kdf_hash(const char* password, const unsigned char* salt, size_t salt_len, unsigned char* out, size_t out_len) {
    if (!password || !salt || !out) return 0;
    return PKCS5_PBKDF2_HMAC(password, (int)strlen(password), salt, (int)salt_len, PBKDF2_ITER, EVP_sha256(), (int)out_len, out) == 1;
}

static int users_find(SessionManager* m, const char* username) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (m->users[i].used && strcmp(m->users[i].username, username) == 0) return i;
    }
    return -1;
}

static int sessions_find(SessionManager* m, const char* token) {
    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (m->sessions[i].used && strcmp(m->sessions[i].token, token) == 0) return i;
    }
    return -1;
}

static void cleanup_expired(SessionManager* m) {
    long now = now_sec();
    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (m->sessions[i].used && m->sessions[i].expires_at < now) {
            m->sessions[i].used = 0;
        }
    }
}

static void map_put_header(Response* r, const char* k, const char* v) {
    if (r->headers_count < 8) {
        snprintf(r->headers[r->headers_count].key, sizeof(r->headers[r->headers_count].key), "%s", k);
        snprintf(r->headers[r->headers_count].value, sizeof(r->headers[r->headers_count].value), "%s", v);
        r->headers_count++;
    }
}

static const char* req_body_get(const Request* req, const char* key) {
    for (int i = 0; i < req->body_count; i++) {
        if (strcmp(req->body[i].key, key) == 0) return req->body[i].value;
    }
    return "";
}

static const char* req_header_get(const Request* req, const char* key) {
    for (int i = 0; i < req->headers_count; i++) {
        if (strcmp(req->headers[i].key, key) == 0) return req->headers[i].value;
    }
    return "";
}

static void resp_json(Response* r, int status, const char* body) {
    r->status = status;
    r->headers_count = 0;
    map_put_header(r, "Content-Type", "application/json; charset=utf-8");
    snprintf(r->body, sizeof(r->body), "%s", body);
}

/* API: register */
static void api_register(SessionManager* m, const Request* req, Response* resp) {
    const char* username = req_body_get(req, "username");
    const char* password = req_body_get(req, "password");
    if (!valid_username(username)) {
        resp_json(resp, 400, "{\"error\":\"Invalid username\"}");
        return;
    }
    if (!strong_password(password)) {
        resp_json(resp, 400, "{\"error\":\"Weak password\"}");
        return;
    }
    if (users_find(m, username) >= 0) {
        resp_json(resp, 400, "{\"error\":\"User exists\"}");
        return;
    }
    int idx = -1;
    for (int i = 0; i < MAX_USERS; i++) {
        if (!m->users[i].used) { idx = i; break; }
    }
    if (idx < 0) {
        resp_json(resp, 500, "{\"error\":\"User store full\"}");
        return;
    }
    User* u = &m->users[idx];
    memset(u, 0, sizeof(*u));
    snprintf(u->username, sizeof(u->username), "%s", username);
    if (RAND_bytes(u->salt, SALT_LEN) != 1) {
        resp_json(resp, 500, "{\"error\":\"RNG failure\"}");
        return;
    }
    if (!kdf_hash(password, u->salt, SALT_LEN, u->hash, HASH_LEN)) {
        resp_json(resp, 500, "{\"error\":\"KDF failure\"}");
        return;
    }
    u->created_at = now_sec();
    u->used = 1;
    resp_json(resp, 201, "{\"status\":\"registered\"}");
}

/* API: login */
static void api_login(SessionManager* m, const Request* req, Response* resp) {
    const char* username = req_body_get(req, "username");
    const char* password = req_body_get(req, "password");
    int uidx = users_find(m, username);
    if (uidx < 0) { resp_json(resp, 401, "{\"error\":\"Invalid credentials\"}"); return; }
    User* u = &m->users[uidx];
    unsigned char calc[HASH_LEN];
    if (!kdf_hash(password, u->salt, SALT_LEN, calc, HASH_LEN)) {
        resp_json(resp, 500, "{\"error\":\"KDF failure\"}");
        return;
    }
    if (CRYPTO_memcmp(calc, u->hash, HASH_LEN) != 0) {
        resp_json(resp, 401, "{\"error\":\"Invalid credentials\"}");
        return;
    }
    long now = now_sec();
    if (now - u->created_at > PW_MAX_AGE) {
        resp_json(resp, 401, "{\"error\":\"Password expired\"}");
        return;
    }
    int sidx = -1;
    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (!m->sessions[i].used) { sidx = i; break; }
    }
    if (sidx < 0) { resp_json(resp, 500, "{\"error\":\"Session store full\"}"); return; }
    unsigned char tokb[32];
    if (RAND_bytes(tokb, sizeof(tokb)) != 1) {
        resp_json(resp, 500, "{\"error\":\"RNG failure\"}");
        return;
    }
    Session* s = &m->sessions[sidx];
    memset(s, 0, sizeof(*s));
    to_hex(tokb, sizeof(tokb), s->token, sizeof(s->token));
    snprintf(s->username, sizeof(s->username), "%s", username);
    s->expires_at = now + SESSION_TTL;
    s->used = 1;

    resp->status = 200;
    resp->headers_count = 0;
    map_put_header(resp, "Set-Cookie", "SID=; HttpOnly; Secure; SameSite=Strict; Path=/"); /* placeholder */
    /* Replace cookie with actual token securely */
    {
        char cookie[256];
        snprintf(cookie, sizeof(cookie), "SID=%s; HttpOnly; Secure; SameSite=Strict; Path=/", s->token);
        resp->headers_count = 0;
        map_put_header(resp, "Set-Cookie", cookie);
    }
    snprintf(resp->body, sizeof(resp->body), "%s", "{\"status\":\"ok\"}");
}

/* Parse Cookie header to extract SID */
static void parse_cookie_sid(const char* cookie, char* sid_out, size_t sid_out_size) {
    sid_out[0] = '\0';
    if (!cookie || !*cookie) return;
    const char* p = cookie;
    while (*p) {
        while (*p == ' ' || *p == ';') p++;
        const char* key_start = p;
        while (*p && *p != '=' && *p != ';') p++;
        size_t key_len = (size_t)(p - key_start);
        if (*p != '=') { while (*p && *p != ';') p++; continue; }
        p++; /* skip '=' */
        const char* val_start = p;
        while (*p && *p != ';') p++;
        size_t val_len = (size_t)(p - val_start);
        if (key_len == 3 && strncmp(key_start, "SID", 3) == 0) {
            size_t copy_len = val_len < sid_out_size - 1 ? val_len : sid_out_size - 1;
            memcpy(sid_out, val_start, copy_len);
            sid_out[copy_len] = '\0';
            return;
        }
        if (*p == ';') p++;
    }
}

/* API: me */
static void api_me(SessionManager* m, const Request* req, Response* resp) {
    cleanup_expired(m);
    const char* cookie = req_header_get(req, "Cookie");
    char sid[TOKEN_LEN+1];
    parse_cookie_sid(cookie, sid, sizeof(sid));
    if (sid[0] == '\0') { resp_json(resp, 401, "{\"error\":\"No session\"}"); return; }
    int sidx = sessions_find(m, sid);
    if (sidx < 0 || m->sessions[sidx].expires_at < now_sec()) {
        resp_json(resp, 401, "{\"error\":\"Invalid or expired session\"}");
        return;
    }
    char uname_safe[128];
    safe_json(m->sessions[sidx].username, uname_safe, sizeof(uname_safe));
    char body[256];
    snprintf(body, sizeof(body), "{\"username\":\"%s\"}", uname_safe);
    resp_json(resp, 200, body);
}

/* API: logout */
static void api_logout(SessionManager* m, const Request* req, Response* resp) {
    const char* cookie = req_header_get(req, "Cookie");
    char sid[TOKEN_LEN+1];
    parse_cookie_sid(cookie, sid, sizeof(sid));
    if (sid[0]) {
        int sidx = sessions_find(m, sid);
        if (sidx >= 0) m->sessions[sidx].used = 0;
    }
    resp->status = 200;
    resp->headers_count = 0;
    map_put_header(resp, "Set-Cookie", "SID=; HttpOnly; Secure; SameSite=Strict; Path=/; Max-Age=0");
    snprintf(resp->body, sizeof(resp->body), "%s", "{\"status\":\"logged_out\"}");
}

/* Router */
static void handle_request(SessionManager* m, const Request* req, Response* resp) {
    if (strcmp(req->path, "/register") == 0) {
        if (strcmp(req->method, "POST") != 0) { resp_json(resp, 405, "Method Not Allowed"); return; }
        api_register(m, req, resp);
    } else if (strcmp(req->path, "/login") == 0) {
        if (strcmp(req->method, "POST") != 0) { resp_json(resp, 405, "Method Not Allowed"); return; }
        api_login(m, req, resp);
    } else if (strcmp(req->path, "/me") == 0) {
        if (strcmp(req->method, "GET") != 0) { resp_json(resp, 405, "Method Not Allowed"); return; }
        api_me(m, req, resp);
    } else if (strcmp(req->path, "/logout") == 0) {
        if (strcmp(req->method, "POST") != 0) { resp_json(resp, 405, "Method Not Allowed"); return; }
        api_logout(m, req, resp);
    } else {
        resp_json(resp, 404, "{\"error\":\"not_found\"}");
    }
}

/* Helpers to build requests */
static Request make_request(const char* method, const char* path) {
    Request r;
    memset(&r, 0, sizeof(r));
    snprintf(r.method, sizeof(r.method), "%s", method);
    snprintf(r.path, sizeof(r.path), "%s", path);
    return r;
}

static void req_add_header(Request* r, const char* k, const char* v) {
    if (r->headers_count < 8) {
        snprintf(r->headers[r->headers_count].key, sizeof(r->headers[r->headers_count].key), "%s", k);
        snprintf(r->headers[r->headers_count].value, sizeof(r->headers[r->headers_count].value), "%s", v);
        r->headers_count++;
    }
}

static void req_add_body(Request* r, const char* k, const char* v) {
    if (r->body_count < 8) {
        snprintf(r->body[r->body_count].key, sizeof(r->body[r->body_count].key), "%s", k);
        snprintf(r->body[r->body_count].value, sizeof(r->body[r->body_count].value), "%s", v);
        r->body_count++;
    }
}

int main(void) {
    SessionManager mgr;
    mgr_init(&mgr);

    // Test 1: Register alice
    Request r1 = make_request("POST", "/register");
    req_add_body(&r1, "username", "alice_1");
    req_add_body(&r1, "password", "Str0ng!Passw0rd");
    Response resp1; handle_request(&mgr, &r1, &resp1);
    printf("T1 status=%d body=%s\n", resp1.status, resp1.body);

    // Test 2: Weak password
    Request r2 = make_request("POST", "/register");
    req_add_body(&r2, "username", "bob");
    req_add_body(&r2, "password", "weak");
    Response resp2; handle_request(&mgr, &r2, &resp2);
    printf("T2 status=%d body=%s\n", resp2.status, resp2.body);

    // Test 3: Login
    Request r3 = make_request("POST", "/login");
    req_add_body(&r3, "username", "alice_1");
    req_add_body(&r3, "password", "Str0ng!Passw0rd");
    Response resp3; handle_request(&mgr, &r3, &resp3);
    const char* set_cookie = "";
    for (int i = 0; i < resp3.headers_count; i++) {
        if (strcmp(resp3.headers[i].key, "Set-Cookie") == 0) {
            set_cookie = resp3.headers[i].value; break;
        }
    }
    printf("T3 status=%d set-cookie-present=%s\n", resp3.status, (set_cookie && *set_cookie) ? "1" : "0");

    // Extract "SID=..." for Cookie header
    char cookie_hdr[256] = {0};
    if (set_cookie && *set_cookie) {
        const char* semi = strchr(set_cookie, ';');
        if (semi) {
            size_t n = (size_t)(semi - set_cookie);
            if (n >= sizeof(cookie_hdr)) n = sizeof(cookie_hdr) - 1;
            memcpy(cookie_hdr, set_cookie, n);
            cookie_hdr[n] = '\0';
        }
    }

    // Test 4: /me
    Request r4 = make_request("GET", "/me");
    if (*cookie_hdr) req_add_header(&r4, "Cookie", cookie_hdr);
    Response resp4; handle_request(&mgr, &r4, &resp4);
    printf("T4 status=%d body=%s\n", resp4.status, resp4.body);

    // Test 5: logout then /me should fail
    Request r5 = make_request("POST", "/logout");
    if (*cookie_hdr) req_add_header(&r5, "Cookie", cookie_hdr);
    Response resp5; handle_request(&mgr, &r5, &resp5);

    Request r6 = make_request("GET", "/me");
    if (*cookie_hdr) req_add_header(&r6, "Cookie", cookie_hdr);
    Response resp6; handle_request(&mgr, &r6, &resp6);

    printf("T5 logout-status=%d me-after-logout-status=%d\n", resp5.status, resp6.status);
    return 0;
}