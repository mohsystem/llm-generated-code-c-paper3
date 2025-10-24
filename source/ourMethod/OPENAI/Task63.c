#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Safe min/max macros */
#define MAX_DECODED_BYTES (1024 * 1024) /* 1 MiB */

static int is_ascii_str(const char *s) {
    if (!s) return 0;
    while (*s) {
        unsigned char c = (unsigned char)*s++;
        if (c > 0x7F) return 0;
    }
    return 1;
}

static char *strip_ws_dup(const char *s) {
    size_t len = strlen(s);
    char *out = (char*)malloc(len + 1);
    if (!out) return NULL;
    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        char c = s[i];
        if (!(c == ' ' || c == '\n' || c == '\r' || c == '\t')) {
            out[j++] = c;
        }
    }
    out[j] = '\0';
    return out;
}

static int is_base64_chars(const char *s) {
    if (!s) return 0;
    for (size_t i = 0; s[i]; i++) {
        unsigned char c = (unsigned char)s[i];
        if (!((c >= 'A' && c <= 'Z') ||
              (c >= 'a' && c <= 'z') ||
              (c >= '0' && c <= '9') ||
              c == '+' || c == '/' || c == '=')) {
            return 0;
        }
    }
    return 1;
}

static int is_valid_utf8(const unsigned char *bytes, size_t n) {
    size_t i = 0;
    while (i < n) {
        unsigned char c = bytes[i];
        if (c <= 0x7F) {
            i++;
        } else if ((c >> 5) == 0x6) {
            if (i + 1 >= n) return 0;
            unsigned char c1 = bytes[i+1];
            if ((c1 & 0xC0) != 0x80) return 0;
            unsigned int code = ((c & 0x1F) << 6) | (c1 & 0x3F);
            if (code < 0x80) return 0;
            i += 2;
        } else if ((c >> 4) == 0xE) {
            if (i + 2 >= n) return 0;
            unsigned char c1 = bytes[i+1], c2 = bytes[i+2];
            if ((c1 & 0xC0) != 0x80 || (c2 & 0xC0) != 0x80) return 0;
            unsigned int code = ((c & 0x0F) << 12) | ((c1 & 0x3F) << 6) | (c2 & 0x3F);
            if (code < 0x800) return 0;
            if (code >= 0xD800 && code <= 0xDFFF) return 0;
            i += 3;
        } else if ((c >> 3) == 0x1E) {
            if (i + 3 >= n) return 0;
            unsigned char c1 = bytes[i+1], c2 = bytes[i+2], c3 = bytes[i+3];
            if ((c1 & 0xC0) != 0x80 || (c2 & 0xC0) != 0x80 || (c3 & 0xC0) != 0x80) return 0;
            unsigned int code = ((c & 0x07) << 18) | ((c1 & 0x3F) << 12) | ((c2 & 0x3F) << 6) | (c3 & 0x3F);
            if (code < 0x10000 || code > 0x10FFFF) return 0;
            i += 4;
        } else {
            return 0;
        }
    }
    return 1;
}

static int contains_disallowed_ctrl(const char *s) {
    for (size_t i = 0; s[i]; i++) {
        unsigned char ch = (unsigned char)s[i];
        if (ch <= 0x1F && ch != 0x09 && ch != 0x0A && ch != 0x0D) {
            return 1;
        }
    }
    return 0;
}

/* Base64 decoding */
static void init_b64_index(int *tbl) {
    for (int i = 0; i < 256; i++) tbl[i] = -1;
    const char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    for (int i = 0; i < 64; i++) {
        tbl[(unsigned char)alphabet[i]] = i;
    }
    tbl[(unsigned char)'='] = -2;
}

static int decode_base64(const char *in, unsigned char **out, size_t *out_len) {
    static int tbl[256];
    static int inited = 0;
    if (!inited) { init_b64_index(tbl); inited = 1; }

    size_t len = strlen(in);
    if (len == 0) {
        *out = (unsigned char*)malloc(1);
        if (!*out) return 0;
        *out_len = 0;
        return 1;
    }
    if (len % 4 != 0) return 0;

    size_t pad = 0;
    if (len >= 2) {
        if (in[len-1] == '=') pad++;
        if (in[len-2] == '=') pad++;
    }

    size_t alloc_len = (len / 4) * 3 - pad;
    if (alloc_len > MAX_DECODED_BYTES) return 0;

    unsigned char *buf = (unsigned char*)malloc(alloc_len ? alloc_len : 1);
    if (!buf) return 0;

    size_t j = 0;
    for (size_t i = 0; i < len; i += 4) {
        int v[4];
        for (int k = 0; k < 4; k++) {
            unsigned char c = (unsigned char)in[i+k];
            int idx = tbl[c];
            if (idx == -1) { free(buf); return 0; }
            v[k] = idx;
        }
        unsigned char b0 = (unsigned char)((v[0] << 2) | ((v[1] & 0x30) >> 4));
        if (j < alloc_len) buf[j++] = b0;
        if (in[i+2] != '=') {
            unsigned char b1 = (unsigned char)(((v[1] & 0x0F) << 4) | ((v[2] & 0x3C) >> 2));
            if (j < alloc_len) buf[j++] = b1;
        }
        if (in[i+3] != '=') {
            unsigned char b2 = (unsigned char)(((v[2] & 0x03) << 6) | v[3]);
            if (j < alloc_len) buf[j++] = b2;
        }
    }

    *out = buf;
    *out_len = alloc_len;
    return 1;
}

/* Base64 encoding for tests */
static char *encode_base64(const char *in) {
    const unsigned char *data = (const unsigned char*)in;
    size_t len = strlen(in);
    const char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    size_t out_len = ((len + 2) / 3) * 4;
    char *out = (char*)malloc(out_len + 1);
    if (!out) return NULL;
    size_t j = 0;
    for (size_t i = 0; i < len; i += 3) {
        unsigned int b0 = data[i];
        unsigned int b1 = (i + 1 < len) ? data[i+1] : 0;
        unsigned int b2 = (i + 2 < len) ? data[i+2] : 0;
        out[j++] = alphabet[(b0 >> 2) & 0x3F];
        out[j++] = alphabet[((b0 & 0x3) << 4) | ((b1 >> 4) & 0x0F)];
        out[j++] = (i + 1 < len) ? alphabet[((b1 & 0x0F) << 2) | ((b2 >> 6) & 0x03)] : '=';
        out[j++] = (i + 2 < len) ? alphabet[b2 & 0x3F] : '=';
    }
    out[j] = '\0';
    return out;
}

/* Trim functions */
static void trim_inplace(char *s) {
    size_t len = strlen(s);
    size_t start = 0;
    while (start < len && (s[start] == ' ' || s[start] == '\t' || s[start] == '\r' || s[start] == '\n')) start++;
    size_t end = len;
    while (end > start && (s[end-1] == ' ' || s[end-1] == '\t' || s[end-1] == '\r' || s[end-1] == '\n')) end--;
    if (start > 0) memmove(s, s + start, end - start);
    s[end - start] = '\0';
}

char *process_request(const char *raw_data_b64, const char *data_type) {
    if (!raw_data_b64 || !data_type) {
        char *e = (char*)malloc(20); if (!e) return NULL; strcpy(e, "ERROR: Null input"); return e;
    }

    char dtype[6] = {0};
    size_t dtlen = strlen(data_type);
    if (dtlen >= sizeof(dtype)) {
        char *e = (char*)malloc(29); if (!e) return NULL; strcpy(e, "ERROR: Unsupported data type"); return e;
    }
    for (size_t i = 0; i < dtlen; i++) dtype[i] = (char)tolower((unsigned char)data_type[i]);
    if (strcmp(dtype, "json") != 0 && strcmp(dtype, "xml") != 0) {
        char *e = (char*)malloc(29); if (!e) return NULL; strcpy(e, "ERROR: Unsupported data type"); return e;
    }

    if (!is_ascii_str(raw_data_b64)) {
        char *e = (char*)malloc(45); if (!e) return NULL; strcpy(e, "ERROR: raw_data must be ASCII/Base64 characters"); return e;
    }

    char *sanitized = strip_ws_dup(raw_data_b64);
    if (!sanitized) { return NULL; }
    if (!is_base64_chars(sanitized)) {
        free(sanitized);
        char *e = (char*)malloc(30); if (!e) return NULL; strcpy(e, "ERROR: Invalid Base64 characters"); return e;
    }

    size_t max_b64_len = ((MAX_DECODED_BYTES + 2) / 3) * 4;
    if (strlen(sanitized) > max_b64_len) {
        free(sanitized);
        char *e = (char*)malloc(22); if (!e) return NULL; strcpy(e, "ERROR: Input too large"); return e;
    }

    unsigned char *decoded = NULL;
    size_t dec_len = 0;
    if (!decode_base64(sanitized, &decoded, &dec_len)) {
        free(sanitized);
        char *e = (char*)malloc(29); if (!e) return NULL; strcpy(e, "ERROR: Base64 decoding failed"); return e;
    }
    free(sanitized);

    if (dec_len > MAX_DECODED_BYTES) {
        free(decoded);
        char *e = (char*)malloc(30); if (!e) return NULL; strcpy(e, "ERROR: Decoded data too large"); return e;
    }

    if (!is_valid_utf8(decoded, dec_len)) {
        free(decoded);
        char *e = (char*)malloc(38); if (!e) return NULL; strcpy(e, "ERROR: Decoded bytes are not valid UTF-8"); return e;
    }

    // Convert to null-terminated string
    char *text = (char*)malloc(dec_len + 1);
    if (!text) { free(decoded); return NULL; }
    memcpy(text, decoded, dec_len);
    text[dec_len] = '\0';
    free(decoded);

    // Trim to check format
    char *trimmed = (char*)malloc(dec_len + 1);
    if (!trimmed) { free(text); return NULL; }
    strcpy(trimmed, text);
    trim_inplace(trimmed);

    if (strcmp(dtype, "json") == 0) {
        if (!(trimmed[0] == '{' || trimmed[0] == '[')) {
            free(trimmed);
            free(text);
            char *e = (char*)malloc(36); if (!e) return NULL; strcpy(e, "ERROR: JSON must start with '{' or '['"); return e;
        }
        if (contains_disallowed_ctrl(text)) {
            free(trimmed);
            free(text);
            char *e = (char*)malloc(49); if (!e) return NULL; strcpy(e, "ERROR: JSON contains disallowed control characters"); return e;
        }
        free(trimmed);
        return text;
    } else {
        if (!(trimmed[0] == '<')) {
            free(trimmed);
            free(text);
            char *e = (char*)malloc(29); if (!e) return NULL; strcpy(e, "ERROR: XML must start with '<'"); return e;
        }
        // Disallow DOCTYPE/ENTITY
        for (char *p = trimmed; *p; ++p) *p = (char)tolower((unsigned char)*p);
        if (strstr(trimmed, "<!doctype") || strstr(trimmed, "<!entity")) {
            free(trimmed);
            free(text);
            char *e = (char*)malloc(45); if (!e) return NULL; strcpy(e, "ERROR: XML contains disallowed DOCTYPE or ENTITY"); return e;
        }
        free(trimmed);
        return text; // Return decoded XML text after basic validation
    }
}

int main(void) {
    const char *json1 = "{\"msg\":\"hello\",\"n\":5}";
    const char *json2 = "[\"hello\",2,true]";
    const char *xml1  = "<root><a>1</a><b>x</b></root>";
    const char *invalid_b64 = "!!!not_base64!!!";
    const char *xml_doctype = "<?xml version=\"1.0\"?><!DOCTYPE foo [<!ENTITY xxe SYSTEM \"file:///etc/passwd\">]><foo>&xxe;</foo>";

    char *b64json1 = encode_base64(json1);
    char *b64json2 = encode_base64(json2);
    char *b64xml1  = encode_base64(xml1);
    char *b64xml_doctype = encode_base64(xml_doctype);

    char *out1 = process_request(b64json1, "json");
    char *out2 = process_request(b64json2, "json");
    char *out3 = process_request(b64xml1,  "xml");
    char *out4 = process_request(invalid_b64, "json");
    char *out5 = process_request(b64xml_doctype, "xml");

    printf("%s\n", out1);
    printf("%s\n", out2);
    printf("%s\n", out3);
    printf("%s\n", out4);
    printf("%s\n", out5);

    free(b64json1);
    free(b64json2);
    free(b64xml1);
    free(b64xml_doctype);
    free(out1);
    free(out2);
    free(out3);
    free(out4);
    free(out5);

    return 0;
}