#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>

#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEADER_SIZE 8192
#define MAX_BODY_SIZE 4096

typedef struct User {
    int id;
    char username[21];
    char email[321];
    int age;
} User;

typedef struct DB {
    pthread_mutex_t mu;
    User users[1024];
    int count;
    int next_id;
} DB;

static DB g_db = {PTHREAD_MUTEX_INITIALIZER, {{0}}, 0, 1};

static int db_add_user(const char* username, const char* email, int age) {
    pthread_mutex_lock(&g_db.mu);
    int id = g_db.next_id++;
    if (g_db.count < (int)(sizeof(g_db.users)/sizeof(g_db.users[0]))) {
        User* u = &g_db.users[g_db.count++];
        u->id = id;
        snprintf(u->username, sizeof(u->username), "%s", username);
        snprintf(u->email, sizeof(u->email), "%s", email);
        u->age = age;
    }
    pthread_mutex_unlock(&g_db.mu);
    return id;
}

static int db_size(void) {
    pthread_mutex_lock(&g_db.mu);
    int n = g_db.count;
    pthread_mutex_unlock(&g_db.mu);
    return n;
}

static bool is_alnum_uscore(char c) {
    return (c == '_') || isalnum((unsigned char)c);
}

static bool is_valid_username(const char* s) {
    if (!s) return false;
    size_t len = strlen(s);
    if (len < 3 || len > 20) return false;
    for (size_t i = 0; i < len; i++) {
        if (!is_alnum_uscore(s[i])) return false;
    }
    return true;
}

static bool is_alpha_str(const char* s) {
    if (!s || !*s) return false;
    for (; *s; s++) {
        if (!isalpha((unsigned char)*s)) return false;
    }
    return true;
}

static bool is_valid_email(const char* s) {
    if (!s) return false;
    size_t len = strlen(s);
    if (len == 0 || len > 320) return false;
    const char* at = strchr(s, '@');
    if (!at || at == s || *(at + 1) == '\0') return false;
    const char* domain = at + 1;
    const char* dot = strrchr(domain, '.');
    if (!dot || dot == domain || *(dot + 1) == '\0') return false;
    const char* tld = dot + 1;
    size_t tld_len = strlen(tld);
    if (tld_len < 2 || tld_len > 63) return false;
    if (!is_alpha_str(tld)) return false;

    const char* p = s;
    const char* allowed_local = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789._%+-";
    const char* allowed_domain = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.-";
    for (; *p && p < at; p++) {
        if (!strchr(allowed_local, *p)) return false;
    }
    for (p = domain; *p; p++) {
        if (!strchr(allowed_domain, *p)) return false;
    }
    return true;
}

static bool is_valid_age(const char* s) {
    if (!s) return false;
    size_t len = strlen(s);
    if (len == 0 || len > 3) return false;
    for (size_t i = 0; i < len; i++) {
        if (!isdigit((unsigned char)s[i])) return false;
    }
    int v = atoi(s);
    return v >= 1 && v <= 120;
}

static int hex_val(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
    if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
    return -1;
}

static bool url_decode(const char* in, char* out, size_t outsz) {
    size_t oi = 0;
    for (size_t i = 0; in[i] != '\0'; i++) {
        char c = in[i];
        if (c == '+') {
            if (oi + 1 >= outsz) return false;
            out[oi++] = ' ';
        } else if (c == '%') {
            if (in[i+1] == '\0' || in[i+2] == '\0') return false;
            int hi = hex_val(in[i+1]);
            int lo = hex_val(in[i+2]);
            if (hi < 0 || lo < 0) return false;
            if (oi + 1 >= outsz) return false;
            out[oi++] = (char)((hi << 4) | lo);
            i += 2;
        } else {
            if (oi + 1 >= outsz) return false;
            out[oi++] = c;
        }
    }
    if (oi >= outsz) return false;
    out[oi] = '\0';
    return true;
}

typedef struct KV {
    char key[33];
    char val[257];
} KV;

static bool parse_form(const char* body, KV* out, size_t* out_count, size_t max_kv) {
    *out_count = 0;
    const char* p = body;
    while (*p) {
        const char* amp = strchr(p, '&');
        size_t pair_len = amp ? (size_t)(amp - p) : strlen(p);
        if (pair_len == 0) {
            if (!amp) break;
            p = amp + 1;
            continue;
        }
        char pair[600];
        if (pair_len >= sizeof(pair)) return false;
        memcpy(pair, p, pair_len);
        pair[pair_len] = '\0';
        char* eq = strchr(pair, '=');
        if (!eq || eq == pair) return false;
        *eq = '\0';
        const char* key_enc = pair;
        const char* val_enc = eq + 1;

        if (*out_count >= max_kv) return false;
        char key_dec[33];
        char val_dec[257];
        if (!url_decode(key_enc, key_dec, sizeof(key_dec))) return false;
        if (!url_decode(val_enc, val_dec, sizeof(val_dec))) return false;
        if (strlen(key_dec) > 32 || strlen(val_dec) > 256) return false;
        snprintf(out[*out_count].key, sizeof(out[*out_count].key), "%s", key_dec);
        snprintf(out[*out_count].val, sizeof(out[*out_count].val), "%s", val_dec);
        (*out_count)++;

        if (!amp) break;
        p = amp + 1;
    }
    return true;
}

static void send_response(int cfd, int code, const char* json) {
    char header[512];
    int n = snprintf(header, sizeof(header),
                     "HTTP/1.1 %d %s\r\n"
                     "Content-Type: application/json; charset=utf-8\r\n"
                     "Content-Length: %zu\r\n"
                     "Connection: close\r\n"
                     "\r\n",
                     code,
                     code == 201 ? "Created" : code == 200 ? "OK" : code == 400 ? "Bad Request"
                     : code == 404 ? "Not Found" : code == 405 ? "Method Not Allowed"
                     : code == 411 ? "Length Required" : code == 413 ? "Payload Too Large"
                     : code == 415 ? "Unsupported Media Type" : "Internal Server Error",
                     json ? strlen(json) : 0u);
    if (n < 0) return;
    send(cfd, header, (size_t)n, 0);
    if (json && *json) {
        send(cfd, json, strlen(json), 0);
    }
}

static bool recv_until(int fd, char** out, size_t* out_len, const char* delim, size_t max_bytes) {
    size_t cap = 1024;
    size_t len = 0;
    char* buf = (char*)malloc(cap);
    if (!buf) return false;
    for (;;) {
        if (len + 512 > cap) {
            size_t ncap = cap * 2;
            if (ncap > max_bytes) ncap = max_bytes;
            if (ncap <= cap) { free(buf); return false; }
            char* nbuf = (char*)realloc(buf, ncap);
            if (!nbuf) { free(buf); return false; }
            buf = nbuf;
            cap = ncap;
        }
        ssize_t r = recv(fd, buf + len, 512, 0);
        if (r <= 0) { free(buf); return false; }
        len += (size_t)r;
        if (len > max_bytes) { free(buf); return false; }
        if (len >= 4) {
            for (size_t i = 0; i + 3 < len; i++) {
                if (buf[i] == '\r' && buf[i+1] == '\n' && buf[i+2] == '\r' && buf[i+3] == '\n') {
                    *out = buf;
                    *out_len = len;
                    return true;
                }
            }
        }
    }
}

static bool recv_exact(int fd, char* out, size_t n) {
    size_t got = 0;
    while (got < n) {
        ssize_t r = recv(fd, out + got, n - got, 0);
        if (r <= 0) return false;
        got += (size_t)r;
    }
    return true;
}

static void handle_client(int cfd) {
    char* raw = NULL;
    size_t raw_len = 0;
    if (!recv_until(cfd, &raw, &raw_len, "\r\n\r\n", MAX_HEADER_SIZE)) {
        close(cfd);
        return;
    }
    size_t hdr_end = 0;
    for (size_t i = 0; i + 3 < raw_len; i++) {
        if (raw[i] == '\r' && raw[i+1] == '\n' && raw[i+2] == '\r' && raw[i+3] == '\n') {
            hdr_end = i;
            break;
        }
    }
    if (hdr_end == 0) { free(raw); close(cfd); return; }

    // First line
    char* first_crlf = memmem(raw, hdr_end, "\r\n", 2);
    size_t rl_len = first_crlf ? (size_t)((char*)first_crlf - raw) : hdr_end;
    char request_line[256];
    size_t copy_len = rl_len < sizeof(request_line)-1 ? rl_len : sizeof(request_line)-1;
    memcpy(request_line, raw, copy_len);
    request_line[copy_len] = '\0';

    char method[16] = {0}, path[64] = {0}, version[16] = {0};
    sscanf(request_line, "%15s %63s %15s", method, path, version);

    if (strcmp(method, "POST") != 0) {
        send_response(cfd, 405, "{\"error\":\"method_not_allowed\"}");
        free(raw);
        close(cfd);
        return;
    }
    if (strcmp(path, "/users") != 0) {
        send_response(cfd, 404, "{\"error\":\"not_found\"}");
        free(raw);
        close(cfd);
        return;
    }

    // Parse headers
    int content_length = -1;
    bool content_type_ok = false;
    size_t pos = rl_len + 2;
    while (pos < hdr_end) {
        char* line_end_ptr = memmem(raw + pos, hdr_end - pos, "\r\n", 2);
        size_t line_end = line_end_ptr ? (size_t)(line_end_ptr - raw) : hdr_end;
        size_t line_len = line_end - pos;
        if (line_len > 0) {
            char line[512];
            size_t lcopy = line_len < sizeof(line)-1 ? line_len : sizeof(line)-1;
            memcpy(line, raw + pos, lcopy);
            line[lcopy] = '\0';
            char* colon = strchr(line, ':');
            if (colon) {
                *colon = '\0';
                char* key = line;
                char* val = colon + 1;
                while (*val == ' ' || *val == '\t') val++;
                for (char* p = key; *p; ++p) *p = (char)tolower((unsigned char)*p);
                if (strcmp(key, "content-type") == 0) {
                    if (strncmp(val, "application/x-www-form-urlencoded", 33) == 0) {
                        content_type_ok = true;
                    }
                } else if (strcmp(key, "content-length") == 0) {
                    content_length = atoi(val);
                }
            }
        }
        if (!line_end_ptr) break;
        pos = line_end + 2;
    }

    if (!content_type_ok) {
        send_response(cfd, 415, "{\"error\":\"unsupported_media_type\"}");
        free(raw);
        close(cfd);
        return;
    }
    if (content_length < 0) {
        send_response(cfd, 411, "{\"error\":\"length_required\"}");
        free(raw);
        close(cfd);
        return;
    }
    if (content_length > (int)MAX_BODY_SIZE) {
        send_response(cfd, 413, "{\"error\":\"payload_too_large\"}");
        free(raw);
        close(cfd);
        return;
    }

    size_t leftover_len = raw_len - (hdr_end + 4);
    char* body = (char*)malloc((size_t)content_length + 1);
    if (!body) { free(raw); close(cfd); return; }
    size_t to_copy = leftover_len < (size_t)content_length ? leftover_len : (size_t)content_length;
    memcpy(body, raw + hdr_end + 4, to_copy);
    size_t need = (size_t)content_length - to_copy;
    bool ok = true;
    if (need > 0) {
        if (!recv_exact(cfd, body + to_copy, need)) ok = false;
    }
    if (!ok) {
        send_response(cfd, 400, "{\"error\":\"incomplete_body\"}");
        free(body);
        free(raw);
        close(cfd);
        return;
    }
    body[content_length] = '\0';
    free(raw);

    KV fields[16];
    size_t nfields = 0;
    if (!parse_form(body, fields, &nfields, 16)) {
        send_response(cfd, 400, "{\"error\":\"invalid_form\"}");
        free(body);
        close(cfd);
        return;
    }
    free(body);

    const char* username = NULL;
    const char* email = NULL;
    const char* ageStr = NULL;
    for (size_t i = 0; i < nfields; i++) {
        if (strcmp(fields[i].key, "username") == 0) username = fields[i].val;
        else if (strcmp(fields[i].key, "email") == 0) email = fields[i].val;
        else if (strcmp(fields[i].key, "age") == 0) ageStr = fields[i].val;
    }

    if (!is_valid_username(username) || !is_valid_email(email) || !is_valid_age(ageStr)) {
        send_response(cfd, 400, "{\"error\":\"invalid_input\"}");
        close(cfd);
        return;
    }
    int age = atoi(ageStr);
    int id = db_add_user(username, email, age);

    char resp[128];
    int n = snprintf(resp, sizeof(resp), "{\"id\":%d,\"status\":\"created\"}", id);
    if (n < 0) n = 0;
    send_response(cfd, 201, resp);
    close(cfd);
}

typedef struct ServerState {
    int fd;
    uint16_t port;
    volatile int ready;
} ServerState;

static void* server_thread(void* arg) {
    ServerState* st = (ServerState*)arg;
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0) return NULL;
    int opt = 1;
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(0);
    if (bind(sfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        close(sfd);
        return NULL;
    }
    socklen_t alen = sizeof(addr);
    if (getsockname(sfd, (struct sockaddr*)&addr, &alen) == 0) {
        st->port = ntohs(addr.sin_port);
    }
    if (listen(sfd, 16) < 0) {
        close(sfd);
        return NULL;
    }
    st->fd = sfd;
    st->ready = 1;

    int handled = 0;
    const int max_requests = 5;
    while (handled < max_requests) {
        struct sockaddr_in caddr;
        socklen_t clen = sizeof(caddr);
        int cfd = accept(sfd, (struct sockaddr*)&caddr, &clen);
        if (cfd < 0) {
            if (errno == EINTR) continue;
            break;
        }
        handle_client(cfd);
        handled++;
    }
    close(sfd);
    return NULL;
}

static bool http_post(uint16_t port, const char* path, const char* body, int* out_code, char* out_body, size_t out_body_sz) {
    int cfd = socket(AF_INET, SOCK_STREAM, 0);
    if (cfd < 0) return false;
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(cfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        close(cfd);
        return false;
    }
    char req[1024];
    int n = snprintf(req, sizeof(req),
                     "POST %s HTTP/1.1\r\n"
                     "Host: 127.0.0.1\r\n"
                     "Content-Type: application/x-www-form-urlencoded; charset=utf-8\r\n"
                     "Content-Length: %zu\r\n"
                     "Connection: close\r\n\r\n",
                     path, strlen(body));
    if (n < 0) { close(cfd); return false; }
    send(cfd, req, (size_t)n, 0);
    if (*body) send(cfd, body, strlen(body), 0);

    char resp[16384];
    size_t total = 0;
    ssize_t r;
    while ((r = recv(cfd, resp + total, sizeof(resp) - total - 1, 0)) > 0) {
        total += (size_t)r;
        if (total >= sizeof(resp) - 1) break;
    }
    resp[total] = '\0';
    close(cfd);

    char* sp1 = strchr(resp, ' ');
    if (!sp1) return false;
    char* sp2 = strchr(sp1 + 1, ' ');
    if (!sp2) return false;
    *sp2 = '\0';
    *out_code = atoi(sp1 + 1);
    char* hdr_end = strstr(sp2 + 1, "\r\n\r\n");
    if (!hdr_end) return false;
    char* body_ptr = hdr_end + 4;
    snprintf(out_body, out_body_sz, "%s", body_ptr);
    return true;
}

int main(void) {
    ServerState st;
    st.fd = -1;
    st.port = 0;
    st.ready = 0;

    pthread_t th;
    if (pthread_create(&th, NULL, server_thread, &st) != 0) {
        fprintf(stderr, "Failed to start server thread\n");
        return 1;
    }

    // wait for ready
    for (int i = 0; i < 100 && !st.ready; i++) {
        usleep(10000);
    }
    if (!st.ready) {
        fprintf(stderr, "Server failed to start\n");
        return 1;
    }
    printf("Server started on port: %u\n", st.port);

    const char* tests[5] = {
        "username=alice_01&email=alice%40example.com&age=30",
        "username=bob&email=invalid_email&age=25",
        "username=ch&email=charlie%40example.com&age=22",
        "username=david12345678901234567890&email=david%40example.com&age=40",
        "username=eve_ok&email=eve.ok%2Btag%40example.co&age=27"
    };
    for (int i = 0; i < 5; i++) {
        int code = 0;
        char body[1024];
        if (http_post(st.port, "/users", tests[i], &code, body, sizeof(body))) {
            printf("Test %d HTTP %d -> %s\n", i + 1, code, body);
        } else {
            printf("Test %d failed to get response\n", i + 1);
        }
    }

    printf("Users stored: %d\n", db_size());
    pthread_join(th, NULL);
    printf("Server stopped.\n");
    return 0;
}