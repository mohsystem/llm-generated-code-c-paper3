#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int is_whitespace(char c) {
    return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

static int is_name_start(unsigned char c) {
    return (isalpha(c) != 0) || c == '_' || c == ':';
}

static int is_name_char(unsigned char c) {
    return (isalnum(c) != 0) || c == '_' || c == '-' || c == '.' || c == ':';
}

static void skip_whitespace(const char* s, size_t n, size_t* i) {
    while (*i < n && is_whitespace(s[*i])) (*i)++;
}

static int starts_with_case_insensitive(const char* s, size_t n, size_t pos, const char* pat) {
    size_t m = strlen(pat);
    if (pos + m > n) return 0;
    for (size_t k = 0; k < m; ++k) {
        unsigned char a = (unsigned char)s[pos + k];
        unsigned char b = (unsigned char)pat[k];
        if ((unsigned char)tolower(a) != (unsigned char)tolower(b)) return 0;
    }
    return 1;
}

static int skip_until(const char* s, size_t n, size_t* i, const char* endToken) {
    size_t m = strlen(endToken);
    if (m == 0) return 0;
    while (*i + m <= n) {
        if (memcmp(s + *i, endToken, m) == 0) {
            *i += m;
            return 1;
        }
        (*i)++;
    }
    return 0;
}

static int skip_doctype(const char* s, size_t n, size_t* i) {
    // Assumes *i at '<' or at the '!' after '<'
    size_t j = *i;
    if (s[j] == '<') j++;
    // Move past DOCTYPE keyword (8 chars)
    if (j + 8 > n) return 0;
    j += 8;
    int in_quote = 0;
    char quote_ch = 0;
    int bracket_depth = 0;
    for (; j < n; ++j) {
        char c = s[j];
        if (in_quote) {
            if (c == quote_ch) in_quote = 0;
            continue;
        }
        if (c == '"' || c == '\'') {
            in_quote = 1;
            quote_ch = c;
        } else if (c == '[') {
            bracket_depth++;
        } else if (c == ']') {
            if (bracket_depth > 0) bracket_depth--;
        } else if (c == '>' && bracket_depth == 0) {
            *i = j + 1;
            return 1;
        }
    }
    return 0;
}

char* get_root_element(const char* xml) {
    const size_t MAX_LEN = 1000000;
    if (xml == NULL) {
        char* out = (char*)malloc(1);
        if (out) out[0] = '\0';
        return out;
    }
    size_t n = strnlen(xml, MAX_LEN + 1);
    if (n == 0 || n > MAX_LEN) {
        char* out = (char*)malloc(1);
        if (out) out[0] = '\0';
        return out;
    }

    size_t i = 0;

    // Skip UTF-8 BOM if present
    if (n >= 3 &&
        (unsigned char)xml[0] == 0xEF &&
        (unsigned char)xml[1] == 0xBB &&
        (unsigned char)xml[2] == 0xBF) {
        i = 3;
    }

    while (1) {
        skip_whitespace(xml, n, &i);
        if (i >= n) break;
        if (xml[i] != '<') break;
        if (i + 1 >= n) break;

        if (xml[i + 1] == '?') {
            // Processing instruction
            i += 2;
            if (!skip_until(xml, n, &i, "?>")) {
                i = n;
                break;
            }
            continue;
        } else if (i + 3 < n && strncmp(xml + i, "<!--", 4) == 0) {
            // Comment
            i += 4;
            if (!skip_until(xml, n, &i, "-->")) {
                i = n;
                break;
            }
            continue;
        } else if (i + 9 <= n && strncmp(xml + i, "<![CDATA[", 9) == 0) {
            // CDATA
            i += 9;
            if (!skip_until(xml, n, &i, "]]>")) {
                i = n;
                break;
            }
            continue;
        } else if (starts_with_case_insensitive(xml, n, i, "<!DOCTYPE")) {
            if (!skip_doctype(xml, n, &i)) {
                i = n;
                break;
            }
            continue;
        } else if (xml[i + 1] == '!') {
            // Other declaration, skip until '>'
            i += 2;
            if (!skip_until(xml, n, &i, ">")) {
                i = n;
                break;
            }
            continue;
        } else {
            // Potential start tag
            break;
        }
    }

    if (i >= n || xml[i] != '<') {
        char* out = (char*)malloc(1);
        if (out) out[0] = '\0';
        return out;
    }
    i++;
    if (i >= n || !is_name_start((unsigned char)xml[i])) {
        char* out = (char*)malloc(1);
        if (out) out[0] = '\0';
        return out;
    }

    size_t start = i;
    i++;
    while (i < n && is_name_char((unsigned char)xml[i])) i++;

    size_t len = (i > start) ? (i - start) : 0;
    char* name = (char*)malloc(len + 1);
    if (!name) {
        char* out = (char*)malloc(1);
        if (out) out[0] = '\0';
        return out;
    }
    if (len > 0) {
        memcpy(name, xml + start, len);
    }
    name[len] = '\0';
    return name;
}

int main(void) {
    const char* tests[] = {
        "<root><child/></root>",
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?><a attr=\"1\">text</a>",
        "  <!--comment-->\n<store><item/></store>",
        "<ns:books xmlns:ns=\"urn:x\"><ns:book/></ns:books>",
        ""
    };
    size_t num = sizeof(tests) / sizeof(tests[0]);
    for (size_t t = 0; t < num; ++t) {
        char* res = get_root_element(tests[t]);
        if (res) {
            printf("%s\n", res);
            free(res);
        } else {
            printf("\n");
        }
    }
    return 0;
}