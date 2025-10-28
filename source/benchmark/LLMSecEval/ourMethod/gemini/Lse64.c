#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include <sys/stat.h>

// You must have the MySQL C client library (libmysqlclient) installed.
// Compile with: gcc your_file.c -o your_app `mysql_config --cflags --libs`
#include <mysql/mysql.h>

// --- Configuration ---
// WARNING: Do not hardcode credentials in production. Use a secure method 
// like environment variables or a secrets management system.
#define DB_HOST "localhost"
#define DB_USER "user"
#define DB_PASS "password"
#define DB_NAME "filedb"

#define UPLOADS_DIR "uploads"
#define MAX_FILE_SIZE (10 * 1024 * 1024) // 10 MB
#define PATH_BUFFER_SIZE 4096

// Forward declarations
char* upload_pdf(const char* original_filename, const void* file_content, size_t content_len, MYSQL *con);
void* download_pdf(const char* filename, MYSQL *con, size_t* out_len);
void setup_test_environment(MYSQL *con);


/**
 * Saves an uploaded PDF file to a secure directory and records its path in the database.
 * @return A dynamically allocated string with the new filename (caller must free), or NULL on failure.
 */
char* upload_pdf(const char* original_filename, const void* file_content, size_t content_len, MYSQL *con) {
    // Rule #1: Validate input
    if (!original_filename || strlen(original_filename) < 5 || 
        strcasecmp(original_filename + strlen(original_filename) - 4, ".pdf") != 0) {
        fprintf(stderr, "Invalid file upload attempt: not a PDF or empty filename.\n");
        return NULL;
    }
    if (!file_content || content_len == 0 || content_len > MAX_FILE_SIZE) {
        fprintf(stderr, "Invalid file upload attempt: File is empty or exceeds max size.\n");
        return NULL;
    }

    // Rule #5: Prevent path traversal by generating a new, safe filename.
    char safe_filename[256];
    snprintf(safe_filename, sizeof(safe_filename), "%ld_%d.pdf", (long)time(NULL), rand() % 10000);

    char file_path[PATH_BUFFER_SIZE];
    snprintf(file_path, sizeof(file_path), "%s/%s", UPLOADS_DIR, safe_filename);

    // Rule #5 & #6: Use realpath to resolve the base directory and check against it
    char uploads_realpath[PATH_BUFFER_SIZE];
    if (!realpath(UPLOADS_DIR, uploads_realpath)) {
        fprintf(stderr, "Error resolving uploads directory path: %s\n", strerror(errno));
        return NULL;
    }

    // Rule #6: Atomically create the file securely
    // O_CREAT | O_EXCL: fail if file exists (prevents TOCTOU)
    // O_NOFOLLOW: do not follow symlinks
    // 0600: restrictive permissions
    int fd = open(file_path, O_WRONLY | O_CREAT | O_EXCL | O_NOFOLLOW, 0600);
    if (fd == -1) {
        fprintf(stderr, "Failed to create file securely: %s\n", strerror(errno));
        return NULL;
    }
    
    ssize_t bytes_written = write(fd, file_content, content_len);
    close(fd);

    if (bytes_written != (ssize_t)content_len) {
        fprintf(stderr, "Failed to write all content to file.\n");
        unlink(file_path); // Cleanup partially written file
        return NULL;
    }

    // Save relative path to DB
    MYSQL_STMT *stmt = mysql_stmt_init(con);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init(), out of memory\n");
        unlink(file_path); return NULL;
    }

    const char *sql = "INSERT INTO files (filepath) VALUES (?)";
    if (mysql_stmt_prepare(stmt, sql, strlen(sql))) {
        fprintf(stderr, "mysql_stmt_prepare() failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt); unlink(file_path); return NULL;
    }

    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char*)file_path;
    bind[0].buffer_length = strlen(file_path);

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt); unlink(file_path); return NULL;
    }
    
    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt); unlink(file_path); return NULL;
    }

    mysql_stmt_close(stmt);
    printf("Successfully uploaded %s and saved path to DB.\n", safe_filename);
    
    char* result_filename = strdup(safe_filename);
    if (!result_filename) {
        fprintf(stderr, "Failed to allocate memory for result.\n");
        return NULL;
    }
    return result_filename;
}

/**
 * Downloads a file by retrieving its path from the database.
 * @return A dynamically allocated buffer with the file content (caller must free), or NULL on failure.
 */
void* download_pdf(const char* filename, MYSQL *con, size_t* out_len) {
    if (!filename || strchr(filename, '/') || strchr(filename, '\\')) {
        fprintf(stderr, "Invalid filename for download.\n");
        return NULL;
    }
    *out_len = 0;

    char file_path_from_db[PATH_BUFFER_SIZE] = {0};
    MYSQL_STMT *stmt = mysql_stmt_init(con);
    const char *sql = "SELECT filepath FROM files WHERE filepath LIKE ?";
    if (mysql_stmt_prepare(stmt, sql, strlen(sql))) {
         fprintf(stderr, "mysql_stmt_prepare() failed: %s\n", mysql_stmt_error(stmt));
         mysql_stmt_close(stmt); return NULL;
    }

    char like_pattern[256];
    snprintf(like_pattern, sizeof(like_pattern), "%%/%s", filename);

    MYSQL_BIND bind[1], result_bind[1];
    memset(bind, 0, sizeof(bind));
    memset(result_bind, 0, sizeof(result_bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = like_pattern;
    bind[0].buffer_length = strlen(like_pattern);
    mysql_stmt_bind_param(stmt, bind);

    unsigned long path_len;
    result_bind[0].buffer_type = MYSQL_TYPE_STRING;
    result_bind[0].buffer = file_path_from_db;
    result_bind[0].buffer_length = sizeof(file_path_from_db) -1;
    result_bind[0].length = &path_len;
    mysql_stmt_bind_result(stmt, result_bind);

    if(mysql_stmt_execute(stmt) || mysql_stmt_store_result(stmt) || mysql_stmt_fetch(stmt)) {
        fprintf(stderr, "DB query for download failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt); return NULL;
    }
    mysql_stmt_close(stmt);

    // Rule #5: Validate path from DB
    char uploads_realpath[PATH_BUFFER_SIZE];
    if (!realpath(UPLOADS_DIR, uploads_realpath)) {
        fprintf(stderr, "Could not resolve uploads directory.\n");
        return NULL;
    }
    char file_realpath[PATH_BUFFER_SIZE];
    if (!realpath(file_path_from_db, file_realpath)) {
        fprintf(stderr, "Could not resolve file path from DB.\n");
        return NULL;
    }
    if (strncmp(file_realpath, uploads_realpath, strlen(uploads_realpath)) != 0) {
        fprintf(stderr, "Security Alert: Attempt to access file outside of uploads directory.\n");
        return NULL;
    }
    
    // Rule #6: Open securely and check file type with fstat
    int fd = open(file_realpath, O_RDONLY | O_NOFOLLOW);
    if (fd == -1) {
        perror("Could not open file for download");
        return NULL;
    }
    struct stat st;
    if (fstat(fd, &st) != 0 || !S_ISREG(st.st_mode)) {
        fprintf(stderr, "Security Alert: Not a regular file.\n");
        close(fd);
        return NULL;
    }
    
    void *buffer = malloc(st.st_size);
    if (!buffer) { close(fd); return NULL; }

    if (read(fd, buffer, st.st_size) != st.st_size) {
        fprintf(stderr, "Failed to read file content.\n");
        free(buffer); close(fd); return NULL;
    }
    
    close(fd);
    *out_len = st.st_size;
    return buffer;
}


void setup_test_environment(MYSQL *con) {
    mkdir(UPLOADS_DIR, 0755);
    const char* create_sql = "CREATE TABLE IF NOT EXISTS files ("
                             "id INT AUTO_INCREMENT PRIMARY KEY,"
                             "filepath VARCHAR(255) NOT NULL UNIQUE,"
                             "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP)";
    const char* truncate_sql = "TRUNCATE TABLE files";

    if (mysql_query(con, create_sql) || mysql_query(con, truncate_sql)) {
        fprintf(stderr, "DB setup failed: %s\n", mysql_error(con));
        fprintf(stderr, "Please check credentials and ensure MySQL is running.\n");
    } else {
        printf("Database table 'files' is ready for testing.\n");
    }
}


int main() {
    srand(time(NULL));
    MYSQL *con = mysql_init(NULL);
    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    if (mysql_real_connect(con, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(con));
        mysql_close(con);
        return 1;
    }
    
    setup_test_environment(con);

    printf("--- Running 5 Test Cases ---\n");
    
    // Test Case 1: Successful upload
    printf("\n[Test 1] Uploading a valid PDF file...\n");
    const char* pdf_content = "This is a fake PDF.";
    char* saved_filename = upload_pdf("mydocument.pdf", pdf_content, strlen(pdf_content), con);
    if (saved_filename) {
        printf("Success! File saved as: %s\n", saved_filename);
    } else {
        printf("Failure. File not uploaded.\n");
    }

    // Test Case 2: Upload non-PDF
    printf("\n[Test 2] Attempting to upload a .txt file...\n");
    char* result2 = upload_pdf("not_a_pdf.txt", "text", 4, con);
    if (!result2) {
        printf("Success! Upload was correctly rejected.\n");
    } else {
        printf("Failure. A non-PDF file was accepted.\n");
        free(result2);
    }

    // Test Case 3: Path traversal
    printf("\n[Test 3] Attempting path traversal: ../../evil.pdf...\n");
    char* result3 = upload_pdf("../../evil.pdf", "evil", 4, con);
    if (result3) {
        printf("Success! Upload succeeded but path traversal was prevented. Safe name: %s\n", result3);
        free(result3);
    } else {
        printf("Failure. Upload failed unexpectedly.\n");
    }

    // Test Case 4: File too large
    printf("\n[Test 4] Attempting to upload a file larger than MAX_FILE_SIZE...\n");
    char* large_content = malloc(MAX_FILE_SIZE + 1);
    if(large_content) {
        char* result4 = upload_pdf("large.pdf", large_content, MAX_FILE_SIZE + 1, con);
        if (!result4) {
            printf("Success! Large file was correctly rejected.\n");
        } else {
            printf("Failure. A large file was accepted.\n");
            free(result4);
        }
        free(large_content);
    }

    // Test Case 5: Successful download
    printf("\n[Test 5] Attempting to download the first valid file...\n");
    if (saved_filename) {
        size_t downloaded_len;
        void* downloaded_content = download_pdf(saved_filename, con, &downloaded_len);
        if (downloaded_content) {
            if (downloaded_len == strlen(pdf_content) && memcmp(downloaded_content, pdf_content, downloaded_len) == 0) {
                printf("Success! Downloaded content matches uploaded content.\n");
            } else {
                printf("Failure. Download failed or content mismatch.\n");
            }
            free(downloaded_content);
        }
    } else {
        printf("Skipping test, as the initial upload failed.\n");
    }
    
    free(saved_filename);
    mysql_close(con);
    return 0;
}