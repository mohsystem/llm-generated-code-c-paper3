/*
 * IMPORTANT: This is a complex example and requires several external libraries.
 * You must have the following installed:
 * 1. libmicrohttpd (HTTP server library)
 * 2. libsqlite3 (Database library)
 * 3. libssl & libcrypto (OpenSSL for password hashing)
 * 4. libjansson (JSON parsing library)
 *
 * On Debian/Ubuntu, you can install them with:
 * sudo apt-get update
 * sudo apt-get install libmicrohttpd-dev libsqlite3-dev libssl-dev libjansson-dev
 *
 * To compile this file:
 * gcc -o task49_c_server task49.c -lmicrohttpd -lsqlite3 -lssl -lcrypto -ljansson
 *
 * Then run the server:
 * ./task49_c_server
 *
 * NOTE: This server is HTTP only. Production systems MUST use HTTPS.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <sqlite3.h>
#include <jansson.h>
#include <openssl/rand.h>
#include <openssl/evp.h>

#define PORT 8080
#define DB_FILE "users.db"
#define POST_BUFFER_SIZE 1024
#define SALT_SIZE 16

// Global database handle for simplicity
sqlite3* db_handle = NULL;

struct RequestContext {
    char* body;
    size_t body_size;
    struct MHD_PostProcessor* post_processor;
};

// --- Helper Functions ---
char* to_hex(const unsigned char* data, size_t len) {
    char* hex_str = malloc(len * 2 + 1);
    if (!hex_str) return NULL;
    for (size_t i = 0; i < len; ++i) {
        sprintf(hex_str + i * 2, "%02x", data[i]);
    }
    hex_str[len * 2] = '\0';
    return hex_str;
}

// --- Database Logic ---
void setup_database() {
    if (sqlite3_open(DB_FILE, &db_handle)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db_handle));
        exit(1);
    }
    char* err_msg = NULL;
    const char* sql = "CREATE TABLE IF NOT EXISTS users ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "username TEXT NOT NULL UNIQUE, "
                      "email TEXT NOT NULL, "
                      "password_hash TEXT NOT NULL, "
                      "salt TEXT NOT NULL);";
    if (sqlite3_exec(db_handle, sql, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db_handle);
        exit(1);
    }
}

// --- HTTP Server Callbacks ---
enum MHD_Result send_json_response(struct MHD_Connection* connection, unsigned int status_code, const char* json_body) {
    struct MHD_Response* response = MHD_create_response_from_buffer(strlen(json_body), (void*)json_body, MHD_RESPMEM_MUST_COPY);
    if (!response) return MHD_NO;
    MHD_add_response_header(response, "Content-Type", "application/json; charset=UTF-8");
    enum MHD_Result ret = MHD_queue_response(connection, status_code, response);
    MHD_destroy_response(response);
    return ret;
}

enum MHD_Result iterate_post_callback(void* coninfo_cls, enum MHD_ValueKind kind, const char* key,
                                      const char* filename, const char* content_type,
                                      const char* transfer_encoding, const char* data,
                                      uint64_t off, size_t size) {
    struct RequestContext* context = coninfo_cls;
    if (size > 0) {
        char* new_body = realloc(context->body, context->body_size + size + 1);
        if (!new_body) return MHD_NO;
        context->body = new_body;
        memcpy(context->body + context->body_size, data, size);
        context->body_size += size;
        context->body[context->body_size] = '\0';
    }
    return MHD_YES;
}

void request_completed_callback(void* cls, struct MHD_Connection* connection,
                                void** con_cls, enum MHD_RequestTerminationCode toe) {
    struct RequestContext* context = *con_cls;
    if (context) {
        if (context->post_processor) {
            MHD_destroy_post_processor(context->post_processor);
        }
        free(context->body);
        free(context);
        *con_cls = NULL;
    }
}

enum MHD_Result handle_request(void* cls, struct MHD_Connection* connection,
                               const char* url, const char* method, const char* version,
                               const char* upload_data, size_t* upload_data_size, void** con_cls) {
    
    if (*con_cls == NULL) {
        struct RequestContext* context = calloc(1, sizeof(struct RequestContext));
        if (!context) return MHD_NO;
        *con_cls = context;

        if (strcmp(method, "POST") == 0) {
            context->post_processor = MHD_create_post_processor(connection, POST_BUFFER_SIZE, iterate_post_callback, context);
            if (!context->post_processor) {
                free(context);
                return MHD_NO;
            }
        }
        return MHD_YES;
    }

    if (strcmp(method, "POST") != 0) {
        return send_json_response(connection, MHD_HTTP_METHOD_NOT_ALLOWED, "{\"error\":\"Method Not Allowed\"}");
    }
    if (strcmp(url, "/api/users") != 0) {
        return send_json_response(connection, MHD_HTTP_NOT_FOUND, "{\"error\":\"Not Found\"}");
    }

    struct RequestContext* context = *con_cls;
    if (*upload_data_size != 0) {
        MHD_post_process(context->post_processor, upload_data, *upload_data_size);
        *upload_data_size = 0;
        return MHD_YES;
    }
    
    // Processing is complete.
    if (context->body_size == 0) {
        return send_json_response(connection, MHD_HTTP_BAD_REQUEST, "{\"error\":\"Request body is empty\"}");
    }

    json_error_t error;
    json_t* root = json_loads(context->body, 0, &error);
    if (!root) {
        return send_json_response(connection, MHD_HTTP_BAD_REQUEST, "{\"error\":\"Invalid JSON format\"}");
    }

    const char *username = NULL, *email = NULL, *password = NULL;
    json_t *j_username, *j_email, *j_password;

    j_username = json_object_get(root, "username");
    j_email = json_object_get(root, "email");
    j_password = json_object_get(root, "password");

    if (!json_is_string(j_username) || !json_is_string(j_email) || !json_is_string(j_password)) {
        json_decref(root);
        return send_json_response(connection, MHD_HTTP_BAD_REQUEST, "{\"error\":\"Missing or invalid fields\"}");
    }
    
    username = json_string_value(j_username);
    email = json_string_value(j_email);
    password = json_string_value(j_password);
    
    if(strlen(username) == 0 || strlen(email) == 0 || strlen(password) == 0) {
        json_decref(root);
        return send_json_response(connection, MHD_HTTP_BAD_REQUEST, "{\"error\":\"Fields cannot be empty\"}");
    }


    unsigned char salt[SALT_SIZE];
    if (RAND_bytes(salt, sizeof(salt)) != 1) {
        json_decref(root);
        return send_json_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, "{\"error\":\"Salt generation failed\"}");
    }

    unsigned char hash[32]; // 256 bits for SHA256
    if (PKCS5_PBKDF2_HMAC(password, strlen(password), salt, sizeof(salt), 600000, EVP_sha256(), sizeof(hash), hash) != 1) {
        json_decref(root);
        return send_json_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, "{\"error\":\"Password hashing failed\"}");
    }

    char* salt_hex = to_hex(salt, sizeof(salt));
    char* hash_hex = to_hex(hash, sizeof(hash));
    if (!salt_hex || !hash_hex) {
         // handle memory allocation failure
        free(salt_hex); free(hash_hex); json_decref(root);
        return send_json_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, "{\"error\":\"Memory allocation failed\"}");
    }

    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO users(username, email, password_hash, salt) VALUES(?,?,?,?);";
    if (sqlite3_prepare_v2(db_handle, sql, -1, &stmt, NULL) != SQLITE_OK) {
        free(salt_hex); free(hash_hex); json_decref(root);
        return send_json_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, "{\"error\":\"DB prepare failed\"}");
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, hash_hex, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, salt_hex, -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE) {
        long long id = sqlite3_last_insert_rowid(db_handle);
        char response_body[128];
        snprintf(response_body, sizeof(response_body), "{\"message\":\"User created successfully\", \"id\":%lld}", id);
        send_json_response(connection, MHD_HTTP_CREATED, response_body);
    } else if (rc == SQLITE_CONSTRAINT) {
        send_json_response(connection, MHD_HTTP_CONFLICT, "{\"error\":\"Username already exists\"}");
    } else {
        fprintf(stderr, "SQL step error: %s\n", sqlite3_errmsg(db_handle));
        send_json_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, "{\"error\":\"Database insertion failed\"}");
    }

    sqlite3_finalize(stmt);
    free(salt_hex);
    free(hash_hex);
    json_decref(root);
    
    return MHD_YES;
}

void print_test_cases() {
    printf("\n--- API Test Cases ---\n");
    printf("Run these curl commands in a separate terminal.\n\n");
    printf("1. Create a new user (Success):\n");
    printf("curl -X POST -H \"Content-Type: application/json\" -d '{\"username\":\"cuser1\",\"email\":\"c1@example.com\",\"password\":\"SecurePass1!\"}' http://localhost:%d/api/users\n\n", PORT);
    printf("2. Create a duplicate user (Conflict):\n");
    printf("curl -X POST -H \"Content-Type: application/json\" -d '{\"username\":\"cuser1\",\"email\":\"another@example.com\",\"password\":\"AnotherPass1!\"}' http://localhost:%d/api/users\n\n", PORT);
    printf("3. Request with missing 'password' field (Bad Request):\n");
    printf("curl -X POST -H \"Content-Type: application/json\" -d '{\"username\":\"cuser2\",\"email\":\"c2@example.com\"}' http://localhost:%d/api/users\n\n", PORT);
    printf("4. Request with malformed JSON (Bad Request):\n");
    printf("curl -X POST -H \"Content-Type: application/json\" -d '{\"username\":\"cuser3\", \"email\":\"c3@example.com\",' http://localhost:%d/api/users\n\n", PORT);
    printf("5. Request to a wrong endpoint (Not Found):\n");
    printf("curl -X POST -H \"Content-Type: application/json\" -d '{\"data\":\"some data\"}' http://localhost:%d/api/nonexistent\n\n", PORT);
}

int main() {
    setup_database();
    
    struct MHD_Daemon* daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                &handle_request, NULL,
                                                MHD_OPTION_NOTIFY_COMPLETED, request_completed_callback, NULL,
                                                MHD_OPTION_END);
    if (!daemon) {
        fprintf(stderr, "Failed to start server daemon.\n");
        sqlite3_close(db_handle);
        return 1;
    }

    printf("Server started on port %d\n", PORT);
    print_test_cases();
    printf("Press Enter to stop the server...\n");
    getchar();

    MHD_stop_daemon(daemon);
    sqlite3_close(db_handle);
    return 0;
}