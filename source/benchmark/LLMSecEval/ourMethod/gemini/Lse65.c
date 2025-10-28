// This code requires the Mongoose library.
// Get mongoose.c and mongoose.h from https://github.com/cesanta/mongoose
// Compile with: gcc -o server your_file.c mongoose.c -I.
// On Windows with MSVC: cl your_file.c mongoose.c /I. /W4
// For this single-file requirement, we'll #include mongoose.c.
#include "mongoose.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <uuid/uuid.h> // Requires libuuid-dev on Debian/Ubuntu, or similar

#ifdef _WIN32
#include <direct.h>
#define MKDIR(path) _mkdir(path)
#else
#define MKDIR(path) mkdir(path, 0755)
#endif


static const char *s_http_addr = "http://0.0.0.0:8080";
static const char *s_upload_dir = "uploads";
#define MAX_FILENAME_LEN 256
#define MAX_PATH_LEN 512

// Note: A real UUID implementation is preferred. This is a placeholder for systems without libuuid.
void generate_simple_uuid(char *dst) {
    long t = time(NULL);
    int r = rand();
    sprintf(dst, "%lx-%x", t, r);
}

// Safely sanitize a filename by extracting its basename.
// Returns a pointer to the basename within the original string.
// Rejects any string containing path separators.
static char* sanitize_filename(char *filename) {
    if (filename == NULL || strpbrk(filename, "/\\") != NULL) {
        return NULL; // Reject any path-like string
    }
    return filename; // Already a basename
}
static void ev_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  if (ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;

    if (mg_http_match_uri(hm, "/")) {
      const char *html_form =
          "<!DOCTYPE html><html><head><title>File Upload</title></head><body>"
          "<h2>Upload PDF File</h2>"
          "<form action=\"/upload\" method=\"post\" enctype=\"multipart/form-data\">"
          "Select PDF file to upload:"
          "<input type=\"file\" name=\"fileToUpload\" id=\"fileToUpload\" accept=\".pdf\" required>"
          "<input type=\"submit\" value=\"Upload PDF\" name=\"submit\">"
          "</form></body></html>";
      mg_http_reply(c, 200, "Content-Type: text/html\r\n", "%s", html_form);

    } else if (mg_http_match_uri(hm, "/upload")) {
      if (mg_vcmp(&hm->method, "POST") != 0) {
        mg_http_reply(c, 405, "", "Method Not Allowed - use multipart/form-data POST");
        return;
      }

      // Iterate multipart form fields
      size_t ofs = 0;
      struct mg_http_part part;
      int found = 0;
      while ((ofs = mg_http_next_multipart(hm->body, ofs, &part)) > 0) {
        // We only care about the file field named "fileToUpload"
        if (part.name.len == 0 || mg_strcmp(part.name, mg_str("fileToUpload")) != 0) continue;
        found = 1;

        // Validate filename presence
        if (part.filename.len == 0) {
          mg_http_reply(c, 400, "", "Bad Request: No filename provided.");
          return;
        }

        // Copy filename into a null-terminated buffer
        char fname_buf[MAX_FILENAME_LEN];
        size_t fl = part.filename.len < sizeof(fname_buf) - 1 ? part.filename.len : sizeof(fname_buf) - 1;
        memcpy(fname_buf, part.filename.buf, fl);
        fname_buf[fl] = '\0';

        // Security: sanitize and enforce .pdf
        char *sanitized_basename = sanitize_filename(fname_buf);
        if (sanitized_basename == NULL || sanitized_basename[0] == '\0') {
          mg_http_reply(c, 400, "", "Bad Request: Invalid filename (contains path characters).");
          return;
        }
        const char *ext = strrchr(sanitized_basename, '.');
        if (!ext || strcasecmp(ext, ".pdf") != 0) {
          mg_http_reply(c, 400, "", "Bad Request: Only PDF files are allowed.");
          return;
        }

        // Unique filename
        char uuid_str[37];
        #ifdef __APPLE__
          generate_simple_uuid(uuid_str);
        #else
          uuid_t binuuid;
          uuid_generate_random(binuuid);
          uuid_unparse_lower(binuuid, uuid_str);
        #endif
        char unique_filename[MAX_FILENAME_LEN];
        snprintf(unique_filename, sizeof(unique_filename), "%s_%s", uuid_str, sanitized_basename);

        // Safe path
        char final_path[MAX_PATH_LEN];
        snprintf(final_path, sizeof(final_path), "%s/%s", s_upload_dir, unique_filename);

        // Write the whole part body (body is fully buffered on MG_EV_HTTP_MSG)
        FILE *fp = fopen(final_path, "wb");
        if (fp == NULL) {
          mg_http_reply(c, 500, "", "Internal Server Error: Could not open file for writing.");
          return;
        }
        size_t wrote = fwrite(part.body.buf, 1, part.body.len, fp);
        fclose(fp);

        if (wrote != part.body.len) {
          mg_http_reply(c, 500, "", "Internal Server Error: Failed to write to file.");
          return;
        }

        printf("File saved successfully: %s (%zu bytes)\n", final_path, (size_t)part.body.len);
        mg_http_reply(c, 200, "", "File uploaded successfully!");
        return;  // Done after saving the first matching part
      }

      if (!found) {
        mg_http_reply(c, 400, "", "Bad Request: Missing form field 'fileToUpload'.");
      }

    } else {
      mg_http_reply(c, 404, "", "Not Found");
    }
  }
  (void) fn_data;
}
int main(void) {
    struct mg_mgr mgr;
    
    // Create upload directory if it doesn't exist
    MKDIR(s_upload_dir);

    mg_mgr_init(&mgr);
    printf("Starting web server on %s\n", s_http_addr);
    if (mg_http_listen(&mgr, s_http_addr, ev_handler, NULL) == NULL) {
        fprintf(stderr, "Cannot start server on %s\n", s_http_addr);
        return 1;
    }

    // --- Test Cases Instructions ---
    printf("\n--- To run test cases, execute the following commands in your terminal ---\n");
    printf("1. Create some dummy files:\n");
    printf("   echo \"%%PDF-1.4...\" > test1.pdf\n");
    printf("   echo \"This is text\" > not_a_pdf.txt\n");
    printf("   echo \"evil\" > evil.pdf\n");
    printf("   touch empty.pdf\n");
    printf("\n2. Run curl commands:\n");
    printf("   # Test 1 (Success): Valid PDF\n");
    printf("   curl -v -F \"fileToUpload=@test1.pdf\" %s/upload\n", s_http_addr);
    printf("   # Test 2 (Fail): Invalid file type\n");
    printf("   curl -v -F \"fileToUpload=@not_a_pdf.txt\" %s/upload\n", s_http_addr);
    printf("   # Test 3 (Fail): Malicious filename with path characters\n");
    printf("   curl -v -F \"fileToUpload=@evil.pdf;filename=../../evil.pdf\" %s/upload\n", s_http_addr);
    printf("   # Test 4 (Success): Normal upload\n");
    printf("   curl -v -F \"fileToUpload=@evil.pdf\" %s/upload\n", s_http_addr);
    printf("   # Test 5 (Fail): No filename provided\n");
    printf("   curl -v -F \"fileToUpload=@empty.pdf;filename=\" %s/upload\n", s_http_addr);
    printf("--------------------------------------------------------------------------\n");

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);

    return 0;
}

// Include mongoose.c directly to make it a "single file" project for simplicity.
