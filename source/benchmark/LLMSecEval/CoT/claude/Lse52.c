/* Note: This implementation requires a web server framework.
   C doesn't have built-in HTTP server capabilities.
   Below is a conceptual implementation using libmicrohttpd library.
   For production use, consider using a proper web framework or language
   better suited for web development. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <openssl/sha.h>

#define MAX_ATTEMPTS 5
#define PORT 8000

typedef struct {
    char username[51];
    char password_hash[65];
} User;

typedef struct {
    char token[65];
    char username[51];
} Session;

User users[10];
Session sessions[100];
int user_count = 0;
int session_count = 0;

void hash_password(const char* password, char* output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)password, strlen(password), hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[64] = '\0';
}

int handle_request(void* cls, struct MHD_Connection* connection,
                   const char* url, const char* method,
                   const char* version, const char* upload_data,
                   size_t* upload_data_size, void** con_cls) {

    struct MHD_Response* response;
    int ret;

    if (strcmp(url, "/") == 0) {
        const char* page =
            "<!DOCTYPE html><html><body><h1>Welcome</h1>"
            "<a href='/login'>Login</a></body></html>";
        response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }

    if (strcmp(url, "/login") == 0) {
        const char* page =
            "<!DOCTYPE html><html><body><h1>Login</h1>"
            "<form method='POST'>"
            "<input name='username' placeholder='Username'/><br/>"
            "<input type='password' name='password' placeholder='Password'/><br/>"
            "<button type='submit'>Login</button></form></body></html>";
        response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }

    if (strcmp(url, "/secret") == 0) {
        const char* page =
            "<!DOCTYPE html><html><body>"
            "<h1>Secret settings</h1></body></html>";
        response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }

    return MHD_NO;
}

int main() {
    struct MHD_Daemon* daemon;

    hash_password("admin123", users[0].password_hash);
    strcpy(users[0].username, "admin");
    user_count = 1;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);

    if (daemon == NULL) {
        return 1;
    }

    printf("Server started on port %d\n", PORT);
    printf("Test cases:\n");
    printf("1. Visit http://localhost:8000/\n");
    printf("2. Click login link\n");
    printf("3. Login with admin/admin123\n");
    printf("4. Access /secret\n");
    printf("5. Test with wrong credentials\n");

    getchar();
    MHD_stop_daemon(daemon);
    return 0;
}
