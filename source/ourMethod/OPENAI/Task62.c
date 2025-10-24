#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    NT_OBJECT, NT_ARRAY, NT_STRING, NT_NUMBER, NT_BOOLEAN, NT_NULL, NT_INVALID
} NodeType;

typedef struct {
    const char* s;
    size_t n;
    size_t i;
} Parser;

typedef struct {
    int dummy;
} ParseError;

static void skip_ws(Parser* p) {
    while (p->i < p->n) {
        char c = p->s[p->i];
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n') p->i++;
        else break;
    }
}

static bool at_end(Parser* p) {
    return p->i >= p->n;
}

static bool peek(Parser* p, char ch) {
    return p->i < p->n && p->s[p->i] == ch;
}

static bool is_digit(char c) { return c >= '0' && c <= '9'; }
static bool is_hex(char c) {
    return (c >= '0' && c <= '9') ||
           (c >= 'a' && c <= 'f') ||
           (c >= 'A' && c <= 'F');
}

static bool expect_char(Parser* p, char ch) {
    if (p->i >= p->n || p->s[p->i] != ch) return false;
    p->i++;
    return true;
}

static bool expect_literal(Parser* p, const char* lit) {
    size_t L = strlen(lit);
    if (p->i + L > p->n) return false;
    if (strncmp(p->s + p->i, lit, L) != 0) return false;
    p->i += L;
    return true;
}

static bool parse_value(Parser* p, NodeType* outType);

static bool parse_string(Parser* p) {
    if (!expect_char(p, '"')) return false;
    while (p->i < p->n) {
        char c = p->s[p->i++];
        if (c == '"') return true;
        if (c == '\\') {
            if (p->i >= p->n) return false;
            char e = p->s[p->i++];
            switch (e) {
                case '"': case '\\': case '/':
                case 'b': case 'f': case 'n': case 'r': case 't':
                    break;
                case 'u':
                    for (int k = 0; k < 4; k++) {
                        if (p->i >= p->n) return false;
                        char h = p->s[p->i++];
                        if (!is_hex(h)) return false;
                    }
                    break;
                default:
                    return false;
            }
        } else {
            if ((unsigned char)c < 0x20) return false;
        }
    }
    return false;
}

static bool parse_number(Parser* p) {
    size_t start = p->i;
    if (peek(p, '-')) p->i++;
    if (p->i >= p->n) return false;
    if (peek(p, '0')) {
        p->i++;
    } else {
        if (!(p->i < p->n && p->s[p->i] >= '1' && p->s[p->i] <= '9')) return false;
        while (p->i < p->n && is_digit(p->s[p->i])) p->i++;
    }
    if (peek(p, '.')) {
        p->i++;
        if (p->i >= p->n || !is_digit(p->s[p->i])) return false;
        while (p->i < p->n && is_digit(p->s[p->i])) p->i++;
    }
    if (p->i < p->n && (p->s[p->i] == 'e' || p->s[p->i] == 'E')) {
        p->i++;
        if (p->i < p->n && (p->s[p->i] == '+' || p->s[p->i] == '-')) p->i++;
        if (p->i >= p->n || !is_digit(p->s[p->i])) return false;
        while (p->i < p->n && is_digit(p->s[p->i])) p->i++;
    }
    return p->i > start;
}

static bool parse_object(Parser* p) {
    if (!expect_char(p, '{')) return false;
    skip_ws(p);
    if (peek(p, '}')) { p->i++; return true; }
    while (1) {
        skip_ws(p);
        if (!parse_string(p)) return false; // key
        skip_ws(p);
        if (!expect_char(p, ':')) return false;
        skip_ws(p);
        NodeType vt;
        if (!parse_value(p, &vt)) return false;
        skip_ws(p);
        if (peek(p, '}')) { p->i++; return true; }
        if (!expect_char(p, ',')) return false;
    }
}

static bool parse_array(Parser* p) {
    if (!expect_char(p, '[')) return false;
    skip_ws(p);
    if (peek(p, ']')) { p->i++; return true; }
    while (1) {
        skip_ws(p);
        NodeType vt;
        if (!parse_value(p, &vt)) return false;
        skip_ws(p);
        if (peek(p, ']')) { p->i++; return true; }
        if (!expect_char(p, ',')) return false;
    }
}

static bool parse_value(Parser* p, NodeType* outType) {
    if (p->i >= p->n) return false;
    char c = p->s[p->i];
    if (c == '{') {
        if (!parse_object(p)) return false;
        *outType = NT_OBJECT; return true;
    }
    if (c == '[') {
        if (!parse_array(p)) return false;
        *outType = NT_ARRAY; return true;
    }
    if (c == '"') {
        if (!parse_string(p)) return false;
        *outType = NT_STRING; return true;
    }
    if (c == 't') {
        if (!expect_literal(p, "true")) return false;
        *outType = NT_BOOLEAN; return true;
    }
    if (c == 'f') {
        if (!expect_literal(p, "false")) return false;
        *outType = NT_BOOLEAN; return true;
    }
    if (c == 'n') {
        if (!expect_literal(p, "null")) return false;
        *outType = NT_NULL; return true;
    }
    if (c == '-' || is_digit(c)) {
        if (!parse_number(p)) return false;
        *outType = NT_NUMBER; return true;
    }
    return false;
}

static const char* node_type_to_str(NodeType t) {
    switch (t) {
        case NT_OBJECT: return "object";
        case NT_ARRAY: return "array";
        case NT_STRING: return "string";
        case NT_NUMBER: return "number";
        case NT_BOOLEAN: return "boolean";
        case NT_NULL: return "null";
        default: return "INVALID";
    }
}

const char* identify_root_element(const char* json) {
    if (json == NULL) return "INVALID";
    size_t len = strlen(json);
    if (len > 1000000u) return "INVALID";
    Parser p;
    p.s = json;
    p.n = len;
    p.i = 0;
    skip_ws(&p);
    NodeType t = NT_INVALID;
    if (!parse_value(&p, &t)) return "INVALID";
    skip_ws(&p);
    if (!at_end(&p)) return "INVALID";
    return node_type_to_str(t);
}

int main(void) {
    const char* tests[5] = {
        "{\"a\":1,\"b\":[true,false,null],\"c\":{\"d\":\"x\"}}",
        "[1,2,3, {\"k\": [\"v\", 2]}]",
        "\"hello world\"",
        "-12.3e-5",
        "true"
    };
    for (int k = 0; k < 5; ++k) {
        const char* res = identify_root_element(tests[k]);
        printf("%s\n", res);
    }
    return 0;
}