#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// This C program demonstrates HTML scraping from provided content (no network) and
// storing results into a local JSONL file acting as a simple database.

typedef struct {
    char *source_id;
    char *title;
    char **links;
    size_t link_count;
    char *timestamp;
} ScrapeResult;

static char *str_dup_safe(const char *s) {
    if (!s) return NULL;
    size_t n = strlen(s);
    char *r = (char *)malloc(n + 1);
    if (!r) return NULL;
    memcpy(r, s, n + 1);
    return r;
}

static char *trim_copy(const char *s) {
    if (!s) return str_dup_safe("");
    const char *b = s;
    while (*b && isspace((unsigned char)*b)) b++;
    const char *e = s + strlen(s);
    while (e > b && isspace((unsigned char)e[-1])) e--;
    size_t n = (size_t)(e - b);
    char *r = (char *)malloc(n + 1);
    if (!r) return NULL;
    memcpy(r, b, n);
    r[n] = '\0';
    return r;
}

static char *to_lower_copy(const char *s) {
    size_t n = strlen(s);
    char *r = (char *)malloc(n + 1);
    if (!r) return NULL;
    for (size_t i = 0; i < n; i++) {
        r[i] = (char)tolower((unsigned char)s[i]);
    }
    r[n] = '\0';
    return r;
}

static char *json_escape(const char *s) {
    if (!s) return str_dup_safe("");
    size_t extra = 0;
    for (const unsigned char *p = (const unsigned char *)s; *p; ++p) {
        switch (*p) {
            case '\"': case '\\': case '\b': case '\f': case ' ': case '\r': case '\t':
                extra += 1; break;
            default:
                if (*p < 0x20) extra += 5;
        }
    }
    size_t n = strlen(s);
    char *r = (char *)malloc(n + extra + 1);
    if (!r) return NULL;
    char *o = r;
    for (const unsigned char *p = (const unsigned char *)s; *p; ++p) {
        switch (*p) {
            case '\"': *o++ = '\\'; *o++ = '\"'; break;
            case '\\': *o++ = '\\'; *o++ = '\\'; break;
            case '\b': *o++ = '\\'; *o++ = 'b'; break;
            case '\f': *o++ = '\\'; *o++ = 'f'; break;
            case '\n': *o++ = '\\'; *o++ = 'n'; break;
            case '\r': *o++ = '\\'; *o++ = 'r'; break;
            case '\t': *o++ = '\\'; *o++ = 't'; break;
            default:
                if (*p < 0x20) {
                    sprintf(o, "\\u%04x", (unsigned)*p);
                    o += 6;
                } else {
                    *o++ = (char)*p;
                }
        }
    }
    *o = '\0';
    return r;
}

static char *now_utc_iso8601(void) {
    time_t t = time(NULL);
    struct tm tm_utc;
#if defined(_WIN32)
    gmtime_s(&tm_utc, &t);
#else
    gmtime_r(&t, &tm_utc);
#endif
    char buf[32];
    snprintf(buf, sizeof(buf), "%04d-%02d-%02dT%02d:%02d:%02dZ",
             tm_utc.tm_year + 1900, tm_utc.tm_mon + 1, tm_utc.tm_mday,
             tm_utc.tm_hour, tm_utc.tm_min, tm_utc.tm_sec);
    return str_dup_safe(buf);
}

static char *extract_title(const char *html) {
    char *lower = to_lower_copy(html);
    if (!lower) return str_dup_safe("");
    const char *open = strstr(lower, "<title");
    if (!open) { free(lower); return str_dup_safe(""); }
    const char *gt = strchr(open, '>');
    if (!gt) { free(lower); return str_dup_safe(""); }
    const char *close = strstr(gt + 1, "</title>");
    if (!close) { free(lower); return str_dup_safe(""); }
    size_t start = (size_t)(gt + 1 - lower);
    size_t end = (size_t)(close - lower);
    size_t len = end > start ? end - start : 0;
    char *inner = (char *)malloc(len + 1);
    if (!inner) { free(lower); return str_dup_safe(""); }
    memcpy(inner, html + (gt + 1 - lower), len);
    inner[len] = '\0';

    // Remove tags inside title
    char *out = (char *)malloc(len + 1);
    if (!out) { free(inner); free(lower); return str_dup_safe(""); }
    size_t j = 0;
    int intag = 0;
    for (size_t i = 0; i < len; i++) {
        char ch = inner[i];
        if (ch == '<') intag = 1;
        else if (ch == '>') intag = 0;
        else if (!intag) out[j++] = ch;
    }
    out[j] = '\0';
    char *trimmed = trim_copy(out);
    if (trimmed && strlen(trimmed) > 512) {
        trimmed[512] = '\0';
    }
    free(out);
    free(inner);
    free(lower);
    if (!trimmed) return str_dup_safe("");
    return trimmed;
}

static void collect_links(const char *html, char ***links_out, size_t *count_out, size_t max_count) {
    *links_out = NULL;
    *count_out = 0;
    size_t cap = 0;

    char *lower = to_lower_copy(html);
    if (!lower) return;

    size_t pos = 0;
    size_t n = strlen(lower);
    while (pos < n && *count_out < max_count) {
        char *a = strstr(lower + pos, "<a");
        if (!a) break;
        size_t idx_a = (size_t)(a - lower);
        char *gt = strchr(lower + idx_a, '>');
        if (!gt) break;
        size_t idx_gt = (size_t)(gt - lower);
        size_t tag_len = idx_gt - idx_a + 1;

        const char *tag_orig = html + idx_a;

        const char *href_pos = strstr(lower + idx_a, "href");
        if (href_pos && (size_t)(href_pos - lower) < idx_gt) {
            const char *eq = strchr(href_pos, '=');
            if (eq && (size_t)(eq - lower) < idx_gt) {
                const char *i = eq + 1;
                while (i < lower + idx_gt && isspace((unsigned char)*i)) i++;
                if (i < lower + idx_gt && (*i == '"' || *i == '\'')) {
                    char quote = *i;
                    const char *j = i + 1;
                    while (j < lower + idx_gt && *j != quote) j++;
                    size_t href_len = (size_t)(j - (i + 1));
                    if (href_len > 0 && href_len <= 2048) {
                        char *href = (char *)malloc(href_len + 1);
                        if (href) {
                            memcpy(href, tag_orig + (i - (lower + idx_a)) + 1, href_len);
                            href[href_len] = '\0';
                            // Check scheme
                            if (strncmp(href, "http://", 7) == 0 || strncmp(href, "https://", 8) == 0) {
                                if (*count_out == cap) {
                                    size_t ncap = cap == 0 ? 8 : cap * 2;
                                    char **tmp = (char **)realloc(*links_out, ncap * sizeof(char *));
                                    if (!tmp) {
                                        free(href);
                                        break;
                                    }
                                    *links_out = tmp;
                                    cap = ncap;
                                }
                                (*links_out)[*count_out] = href;
                                (*count_out)++;
                            } else {
                                free(href);
                            }
                        }
                    }
                }
            }
        }
        pos = idx_gt + 1;
        (void)tag_len;
    }
    free(lower);
}

static void free_scrape_result(ScrapeResult *r) {
    if (!r) return;
    free(r->source_id);
    free(r->title);
    for (size_t i = 0; i < r->link_count; i++) {
        free(r->links[i]);
    }
    free(r->links);
    free(r->timestamp);
    r->source_id = NULL;
    r->title = NULL;
    r->links = NULL;
    r->link_count = 0;
    r->timestamp = NULL;
}

static ScrapeResult scrape_from_html(const char *source_id, const char *html) {
    ScrapeResult r;
    r.source_id = str_dup_safe(source_id ? source_id : "");
    // Limit size to 1.2MB
    size_t len = html ? strlen(html) : 0;
    const size_t MAX = 1200000;
    char *limited = NULL;
    if (!html) {
        limited = str_dup_safe("");
    } else if (len > MAX) {
        limited = (char *)malloc(MAX + 1);
        if (limited) {
            memcpy(limited, html, MAX);
            limited[MAX] = '\0';
        }
    } else {
        limited = str_dup_safe(html);
    }

    r.title = extract_title(limited ? limited : "");
    r.links = NULL;
    r.link_count = 0;
    collect_links(limited ? limited : "", &r.links, &r.link_count, 1000);
    r.timestamp = now_utc_iso8601();

    if (limited) free(limited);
    return r;
}

static int store_jsonl_record(const char *db_file, const ScrapeResult *r) {
    if (!db_file || !r) return 0;
    FILE *f = fopen(db_file, "ab");
    if (!f) return 0;

    char *src = json_escape(r->source_id ? r->source_id : "");
    char *ttl = json_escape(r->title ? r->title : "");
    char *ts = json_escape(r->timestamp ? r->timestamp : "");
    if (!src || !ttl || !ts) {
        if (src) free(src);
        if (ttl) free(ttl);
        if (ts) free(ts);
        fclose(f);
        return 0;
    }

    // Write JSON line
    fputs("{\"source\":\"", f);
    fputs(src, f);
    fputs("\",\"title\":\"", f);
    fputs(ttl, f);
    fputs("\",\"links\":[", f);
    for (size_t i = 0; i < r->link_count; i++) {
        if (i) fputc(',', f);
        char *e = json_escape(r->links[i] ? r->links[i] : "");
        if (!e) { /* skip */ }
        else {
            fputc('\"', f);
            fputs(e, f);
            fputc('\"', f);
            free(e);
        }
    }
    fputs("],\"timestamp\":\"", f);
    fputs(ts, f);
    fputs("\"}\n", f);

    free(src);
    free(ttl);
    free(ts);
    int ok = (fflush(f) == 0);
    fclose(f);
    return ok;
}

int main(void) {
    const char *db_file = "c_scrape_db.jsonl";
    struct {
        const char *id;
        const char *html;
    } tests[5] = {
        {"html:test1", "<!doctype html><html><head><title>Example Domain</title></head><body>"
                       "<a href=\"https://www.iana.org/domains/reserved\">IANA</a></body></html>"},
        {"html:test2", "<html><head><title>Wikipedia</title></head><body>"
                       "<a href='https://www.wikipedia.org/'>Home</a>"
                       "<a href='http://example.com/path'>Example</a></body></html>"},
        {"html:test3", "<html><head><title>GNU Site</title></head><body>"
                       "<a href=\"https://www.gnu.org/licenses/\">Licenses</a></body></html>"},
        {"html:test4", "<html><head><title>HttpBin</title></head><body>"
                       "<a href='https://httpbin.org/get'>Get</a>"
                       "<a href='mailto:test@example.com'>Mail</a></body></html>"},
        {"html:test5", "<html><head><title>Mixed Links</title></head><body>"
                       "<a href='https://a.example.com'>A</a>"
                       "<a href='http://b.example.com'>B</a>"
                       "<a href='#anchor'>C</a></body></html>"},
    };

    for (int i = 0; i < 5; i++) {
        ScrapeResult r = scrape_from_html(tests[i].id, tests[i].html);
        int ok = store_jsonl_record(db_file, &r);
        printf("Scraped: %s | title=%s | links=%zu | stored=%s\n",
               r.source_id ? r.source_id : "",
               r.title ? r.title : "",
               r.link_count,
               ok ? "yes" : "no");
        free_scrape_result(&r);
    }
    return 0;
}