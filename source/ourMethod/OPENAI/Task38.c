#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <ctype.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8083
#define MAX_HEADER 8192
#define MAX_BODY 4096
#define MAX_MESSAGE_LEN 200

static volatile sig_atomic_t g_running = 1;

static void handle_sigint(int sig) {
    (void)sig;
    g_running = 0;
}

static void safe_str_append(char *dst, size_t dst_size, const char *src) {
    size_t dlen = strnlen(dst, dst_size);
    size_t slen = strlen(src);
    if (dlen >= dst_size) return;
    size_t copy = (slen < (dst_size - dlen - 1)) ? slen : (dst_size - dlen - 1);
    memcpy(dst + dlen, src, copy);
    dst[dlen + copy] = '\0';
}

static char *html_escape(const char *s) {
    if (!s) {
        char *empty = (char*)calloc(1, 1);
        return empty;
    }
    size_t len = strlen(s);
    size_t cap = len * 6 + 1; // worst-case
    char *out = (char*)malloc(cap);
    if (!out) return NULL;
    size_t o = 0;
    for (size_t i = 0; i < len; i++) {
        char c = s[i];
        const char *rep = NULL;
        switch (c) {
            case '&': rep = "&amp;"; break;
            case '<': rep = "&lt;"; break;
            case '>': rep = "&gt;"; break;
            case '"': rep = "&quot;"; break;
            case '\'': rep = "&#39;"; break;
            default: break;
        }
        if (rep) {
            size_t rlen = strlen(rep);
            if (o + rlen >= cap) { free(out); return NULL; }
            memcpy(out + o, rep, rlen);
            o += rlen;
        } else {
            if (o + 1 >= cap) { free(out); return NULL; }
            out[o++] = c;
        }
    }
    if (o >= cap) { free(out); return NULL; }
    out[o] = '\0';
    return out;
}

static char *sanitize_input(const char *in, size_t max_len) {
    if (!in) {
        char *empty = (char*)calloc(1, 1);
        return empty;
    }
    // trim
    size_t len = strlen(in);
    size_t start = 0, end = len;
    while (start < end && isspace((unsigned char)in[start])) start++;
    while (end > start && isspace((unsigned char)in[end - 1])) end--;
    size_t out_cap = (max_len + 1);
    char *out = (char*)malloc(out_cap);
    if (!out) return NULL;
    size_t o = 0;
    for (size_t i = start; i < end && o < max_len; i++) {
        unsigned char c = (unsigned char)in[i];
        if (c == '\n' || c == '\r' || c == '\t' || !iscntrl(c)) {
            if (iscntrl(c) && !(c == '\n' || c == '\r' || c == '\t')) continue;
            out[o++] = (char)c;
        }
    }
    out[o] = '\0';
    return out;
}

static int hexval(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
    if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
    return -1;
}

static bool url_decode(const char *in, char *out, size_t out_size) {
    size_t o = 0;
    for (size_t i = 0; in[i] != '\0'; i++) {
        char c = in[i];
        if (c == '+') {
            if (o + 1 >= out_size) return false;
            out[o++] = ' ';
        } else if (c == '%' && in[i + 1] && in[i + 2]) {
            int h1 = hexval(in[i + 1]);
            int h2 = hexval(in[i + 2]);
            if (h1 < 0 || h2 < 0) return false;
            if (o + 1 >= out_size) return false;
            out[o++] = (char)((h1 << 4) | h2);
            i += 2;
        } else {
            if (o + 1 >= out_size) return false;
            out[o++] = c;
        }
    }
    if (o >= out_size) return false;
    out[o] = '\0';
    return true;
}

static void parse_form(const char *body, char *message_out, size_t message_out_size) {
    // Simple parser for message=...
    message_out[0] = '\0';
    const char *p = body;
    while (*p) {
        const char *amp = strchr(p, '&');
        size_t pair_len = amp ? (size_t)(amp - p) : strlen(p);
        const char *eq = memchr(p, '=', pair_len);
        if (eq) {
            size_t key_len = (size_t)(eq - p);
            size_t val_len = pair_len - key_len - 1;
            char key[64];
            char val_enc[1024];
            size_t kcopy = key_len < sizeof(key) - 1 ? key_len : sizeof(key) - 1;
            memcpy(key, p, kcopy);
            key[kcopy] = '\0';
            size_t vcopy = val_len < sizeof(val_enc) - 1 ? val_len : sizeof(val_enc) - 1;
            memcpy(val_enc, eq + 1, vcopy);
            val_enc[vcopy] = '\0';
            if (strcmp(key, "message") == 0) {
                char decoded[1024];
                if (url_decode(val_enc, decoded, sizeof(decoded))) {
                    // copy safely
                    strncpy(message_out, decoded, message_out_size - 1);
                    message_out[message_out_size - 1] = '\0';
                }
            }
        }
        if (!amp) break;
        p = amp + 1;
    }
}

static bool recv_until(int fd, char **out, size_t *out_len, const char *delim, size_t max_bytes) {
    size_t cap = 2048;
    size_t len = 0;
    char *buf = (char*)malloc(cap);
    if (!buf) return false;
    while (true) {
        if (len + 1024 > cap) {
            if (cap > max_bytes / 2) { free(buf); return false; }
            cap *= 2;
            char *nbuf = (char*)realloc(buf, cap);
            if (!nbuf) { free(buf); return false; }
            buf = nbuf;
        }
        ssize_t r = recv(fd, buf + len, 1024, 0);
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

static bool send_all(int fd, const char *data, size_t len) {
    size_t sent = 0;
    while (sent < len) {
        ssize_t w = send(fd, data + sent, len - sent, 0);
        if (w <= 0) return false;
        sent += (size_t)w;
    }
    return true;
}

static void send_text_response(int fd, int code, const char *reason, const char *content_type, const char *body) {
    char header[512];
    size_t body_len = body ? strlen(body) : 0;
    int n = snprintf(header, sizeof(header),
                     "HTTP/1.1 %d %s\r\n"
                     "Content-Type: %s\r\n"
                     "X-Content-Type-Options: nosniff\r\n"
                     "Content-Security-Policy: default-src 'none'; style-src 'self' 'unsafe-inline'; form-action 'self'\r\n"
                     "Content-Length: %zu\r\n"
                     "Connection: close\r\n\r\n",
                     code, reason, content_type, body_len);
    if (n < 0 || (size_t)n >= sizeof(header)) return;
    send_all(fd, header, (size_t)n);
    if (body_len > 0) send_all(fd, body, body_len);
}

static char *render_page(const char *result_html) {
    const char *head =
        "<!DOCTYPE html><html lang=\"en\"><head>"
        "<meta charset=\"UTF-8\">"
        "<meta http-equiv=\"X-Content-Type-Options\" content=\"nosniff\">"
        "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
        "<title>Echo App</title>"
        "<style>body{font-family:sans-serif;margin:2rem;}input[type=text]{width:300px;max-width:90%;padding:.4rem;}button{padding:.4rem .8rem;margin-left:.5rem;} .result{margin-top:1rem;padding:.8rem;background:#f4f6f8;border:1px solid #dfe3e8;border-radius:6px;}</style>"
        "</head><body>"
        "<h1>Echo App</h1>"
        "<form method=\"post\" action=\"/submit\" autocomplete=\"off\">"
        "<label for=\"message\">Message (max 200 chars):</label><br>"
        "<input id=\"message\" name=\"message\" type=\"text\" maxlength=\"200\" required>"
        "<button type=\"submit\">Send</button>"
        "</form>";
    const char *tail = "</body></html>";

    size_t size = strlen(head) + strlen(tail) + 1;
    if (result_html) size += strlen(result_html) + strlen("<div class=\"result\"></div>");
    char *html = (char*)malloc(size);
    if (!html) return NULL;
    html[0] = '\0';
    safe_str_append(html, size, head);
    if (result_html) {
        safe_str_append(html, size, "<div class=\"result\">");
        safe_str_append(html, size, result_html);
        safe_str_append(html, size, "</div>");
    }
    safe_str_append(html, size, tail);
    return html;
}

static void handle_client(int fd) {
    char *header = NULL;
    size_t hlen = 0;
    if (!recv_until(fd, &header, &hlen, "\r\n\r\n", MAX_HEADER)) {
        close(fd);
        return;
    }
    // Find header end
    size_t hdr_end = 0;
    for (size_t i = 0; i + 3 < hlen; i++) {
        if (header[i] == '\r' && header[i+1] == '\n' && header[i+2] == '\r' && header[i+3] == '\n') {
            hdr_end = i + 4;
            break;
        }
    }
    if (hdr_end == 0) { free(header); close(fd); return; }

    // Request line
    char *line_end = memchr(header, '\n', hlen);
    if (!line_end) { free(header); close(fd); return; }
    size_t rl_len = (size_t)(line_end - header);
    char reqline[512];
    size_t rcopy = rl_len < sizeof(reqline) - 1 ? rl_len : sizeof(reqline) - 1;
    memcpy(reqline, header, rcopy);
    reqline[rcopy] = '\0';
    char method[8], path[256], version[16];
    method[0] = path[0] = version[0] = '\0';
    sscanf(reqline, "%7s %255s %15s", method, path, version);

    // Headers: find Content-Length and Content-Type
    long content_length = -1;
    char content_type[128]; content_type[0] = '\0';
    char *p = header + rl_len + 1;
    while ((size_t)(p - header) < hdr_end) {
        char *nl = memchr(p, '\n', header + hdr_end - p);
        if (!nl) break;
        size_t l = (size_t)(nl - p);
        if (l > 0) {
            char line[512];
            size_t lcopy = l < sizeof(line) - 1 ? l : sizeof(line) - 1;
            memcpy(line, p, lcopy);
            line[lcopy] = '\0';
            // to lowercase name up to ':'
            char *colon = strchr(line, ':');
            if (colon) {
                *colon = '\0';
                char *value = colon + 1;
                while (*value == ' ' || *value == '\t') value++;
                if (strncasecmp(line, "Content-Length", 14) == 0) {
                    content_length = strtol(value, NULL, 10);
                } else if (strncasecmp(line, "Content-Type", 12) == 0) {
                    strncpy(content_type, value, sizeof(content_type) - 1);
                    content_type[sizeof(content_type) - 1] = '\0';
                }
            }
        }
        p = nl + 1;
    }

    size_t leftover_len = hlen - hdr_end;
    char *leftover = header + hdr_end;

    if (strcmp(method, "GET") == 0 && (strcmp(path, "/") == 0 || strcmp(path, "/index.html") == 0)) {
        char *page = render_page(NULL);
        if (!page) { free(header); close(fd); return; }
        send_text_response(fd, 200, "OK", "text/html; charset=UTF-8", page);
        free(page);
        free(header);
        close(fd);
        return;
    } else if (strcmp(method, "POST") == 0 && strcmp(path, "/submit") == 0) {
        if (content_length < 0 || content_length > MAX_BODY) {
            send_text_response(fd, 413, "Payload Too Large", "text/plain; charset=UTF-8", "Payload Too Large");
            free(header);
            close(fd);
            return;
        }
        char ct_lower[128];
        size_t ctlen = strnlen(content_type, sizeof(content_type));
        for (size_t i = 0; i < ctlen && i < sizeof(ct_lower)-1; i++) {
            ct_lower[i] = (char)tolower((unsigned char)content_type[i]);
        }
        ct_lower[ctlen < sizeof(ct_lower)-1 ? ctlen : sizeof(ct_lower)-1] = '\0';
        if (strncmp(ct_lower, "application/x-www-form-urlencoded", 33) != 0) {
            send_text_response(fd, 400, "Bad Request", "text/plain; charset=UTF-8", "Unsupported Content-Type");
            free(header);
            close(fd);
            return;
        }
        char *body = (char*)malloc((size_t)content_length + 1);
        if (!body) { free(header); close(fd); return; }
        size_t copied = 0;
        if (leftover_len > 0) {
            size_t c = leftover_len > (size_t)content_length ? (size_t)content_length : leftover_len;
            memcpy(body, leftover, c);
            copied = c;
        }
        while (copied < (size_t)content_length) {
            ssize_t r = recv(fd, body + copied, (size_t)content_length - copied, 0);
            if (r <= 0) { free(body); free(header); close(fd); return; }
            copied += (size_t)r;
            if (copied > MAX_BODY) { free(body); free(header); close(fd); return; }
        }
        body[content_length] = '\0';

        char message_raw[1024];
        parse_form(body, message_raw, sizeof(message_raw));

        char *san = sanitize_input(message_raw, MAX_MESSAGE_LEN);
        if (!san) { free(body); free(header); close(fd); return; }
        char *esc = html_escape(san);
        if (!esc) { free(san); free(body); free(header); close(fd); return; }

        char result[2048];
        snprintf(result, sizeof(result), "You submitted: <strong>%s</strong>", esc);
        char *page = render_page(result);
        if (page) {
            send_text_response(fd, 200, "OK", "text/html; charset=UTF-8", page);
            free(page);
        }
        free(esc);
        free(san);
        free(body);
        free(header);
        close(fd);
        return;
    } else {
        send_text_response(fd, 404, "Not Found", "text/plain; charset=UTF-8", "Not Found");
        free(header);
        close(fd);
        return;
    }
}

static void run_tests(void) {
    const char *tests[5] = {
        "<script>alert(1)</script>",
        "Hello & Goodbye",
        "   trims   ",
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", // >200
        "Controls\x01\x02removed"
    };
    for (int i = 0; i < 5; i++) {
        char *san = sanitize_input(tests[i], MAX_MESSAGE_LEN);
        char *esc = html_escape(san);
        printf("Test %d: input=[%s] sanitized=[%s] escaped=[%s]\n", i + 1, tests[i], san ? san : "", esc ? esc : "");
        free(san);
        free(esc);
    }
}

int main(void) {
    run_tests();

    signal(SIGINT, handle_sigint);

    int srv = socket(AF_INET, SOCK_STREAM, 0);
    if (srv < 0) {
        perror("socket");
        return 1;
    }
    int yes = 1;
    if (setsockopt(srv, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0) {
        perror("setsockopt");
        close(srv);
        return 1;
    }
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(srv, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(srv);
        return 1;
    }
    if (listen(srv, 16) < 0) {
        perror("listen");
        close(srv);
        return 1;
    }
    printf("Server started on http://127.0.0.1:%d/\n", PORT);
    while (g_running) {
        struct sockaddr_in cli;
        socklen_t clen = sizeof(cli);
        int fd = accept(srv, (struct sockaddr*)&cli, &clen);
        if (fd < 0) {
            if (errno == EINTR) break;
            perror("accept");
            continue;
        }
        handle_client(fd);
    }
    close(srv);
    printf("Server stopped.\n");
    return 0;
}