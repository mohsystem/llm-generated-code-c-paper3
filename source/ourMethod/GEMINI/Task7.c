#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdatomic.h>
#include <regex.h>
#include <stdbool.h>
#include <time.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>

// Note: Compile with: gcc your_file.c -o chat_system_c -lssl -lcrypto -lpthread -D_GNU_SOURCE
// This code uses POSIX sockets and will not work on Windows without modification (e.g., using Winsock).

#define PORT 12345
#define BUFFER_SIZE 1024
#define USER_DB_FILE "users.db"
#define VALID_USERNAME_REGEX "^[a-zA-Z0-9_]{3,16}$"

#define SALT_LENGTH 16
#define PBKDF2_ITER 210000
#define KEY_LENGTH 32 // 256 bits

static pthread_mutex_t db_mutex = PTHREAD_MUTEX_INITIALIZER;
static bool server_running = true;

// Utility to convert byte array to hex string
void to_hex(char *dest, const unsigned char *src, size_t len) {
    for (size_t i = 0; i < len; i++) {
        sprintf(dest + (i * 2), "%02x", src[i]);
    }
    dest[len * 2] = '\0';
}

// Utility to convert hex string to byte array
int from_hex(unsigned char *dest, const char *src, size_t dest_len) {
    size_t src_len = strlen(src);
    if (src_len % 2 != 0 || src_len / 2 != dest_len) return -1;
    for (size_t i = 0; i < dest_len; i++) {
        if (sscanf(src + 2 * i, "%2hhx", &dest[i]) != 1) return -1;
    }
    return 0;
}

int hash_password(unsigned char *hash, const char *password, const unsigned char *salt) {
    return PKCS5_PBKDF2_HMAC(password, strlen(password), salt, SALT_LENGTH, PBKDF2_ITER, EVP_sha256(), KEY_LENGTH, hash);
}

int add_user(const char *username, const char *password) {
    if (!username || !password || strlen(username) == 0 || strlen(password) == 0) return 0;

    regex_t regex;
    if (regcomp(&regex, VALID_USERNAME_REGEX, REG_EXTENDED) != 0) return 0;
    int match = regexec(&regex, username, 0, NULL, 0);
    regfree(&regex);
    if (match != 0) return 0;
    
    pthread_mutex_lock(&db_mutex);

    FILE *f = fopen(USER_DB_FILE, "r");
    if (f) {
        char line[BUFFER_SIZE];
        char existing_user[BUFFER_SIZE];
        while (fgets(line, sizeof(line), f)) {
            sscanf(line, "%[^:]", existing_user);
            if (strcmp(username, existing_user) == 0) {
                fclose(f);
                pthread_mutex_unlock(&db_mutex);
                return 0; // User exists
            }
        }
        fclose(f);
    }

    f = fopen(USER_DB_FILE, "a");
    if (!f) {
        pthread_mutex_unlock(&db_mutex);
        return 0;
    }

    unsigned char salt[SALT_LENGTH];
    unsigned char hash[KEY_LENGTH];
    if (RAND_bytes(salt, sizeof(salt)) != 1 || hash_password(hash, password, salt) != 1) {
        fclose(f);
        pthread_mutex_unlock(&db_mutex);
        return 0;
    }

    char salt_hex[SALT_LENGTH * 2 + 1];
    char hash_hex[KEY_LENGTH * 2 + 1];
    to_hex(salt_hex, salt, sizeof(salt));
    to_hex(hash_hex, hash, sizeof(hash));
    
    fprintf(f, "%s:%s:%s\n", username, salt_hex, hash_hex);
    
    fclose(f);
    pthread_mutex_unlock(&db_mutex);
    return 1;
}

int authenticate_user(const char *username, const char *password) {
    pthread_mutex_lock(&db_mutex);
    FILE *f = fopen(USER_DB_FILE, "r");
    if (!f) {
        pthread_mutex_unlock(&db_mutex);
        return 0;
    }

    char line[BUFFER_SIZE];
    int authenticated = 0;
    while (fgets(line, sizeof(line), f)) {
        char file_user[BUFFER_SIZE], salt_hex[BUFFER_SIZE], hash_hex[BUFFER_SIZE];
        if (sscanf(line, "%[^:]:%[^:]:%s", file_user, salt_hex, hash_hex) == 3) {
            if (strcmp(username, file_user) == 0) {
                unsigned char salt[SALT_LENGTH];
                unsigned char stored_hash[KEY_LENGTH];
                if (from_hex(salt, salt_hex, SALT_LENGTH) != 0 || from_hex(stored_hash, hash_hex, KEY_LENGTH) != 0) {
                    continue;
                }
                
                unsigned char provided_hash[KEY_LENGTH];
                if (hash_password(provided_hash, password, salt) != 1) continue;

                if (CRYPTO_memcmp(stored_hash, provided_hash, KEY_LENGTH) == 0) {
                    authenticated = 1;
                }
                break;
            }
        }
    }
    
    fclose(f);
    pthread_mutex_unlock(&db_mutex);
    return authenticated;
}

void* handle_client(void *socket_desc) {
    int sock = *(int*)socket_desc;
    free(socket_desc);
    char buffer[BUFFER_SIZE] = {0};

    if (read(sock, buffer, BUFFER_SIZE - 1) <= 0) {
        close(sock);
        return NULL;
    }

    char *saveptr;
    char *command = strtok_r(buffer, " \n\r", &saveptr);
    char *username = strtok_r(NULL, " \n\r", &saveptr);
    char *password = strtok_r(NULL, " \n\r", &saveptr);

    char response[BUFFER_SIZE];
    if (command && username && password) {
        if (strcmp(command, "REGISTER") == 0) {
            snprintf(response, sizeof(response), "%s\n", add_user(username, password) ? "REGISTER_OK" : "REGISTER_FAIL");
        } else if (strcmp(command, "LOGIN") == 0) {
            snprintf(response, sizeof(response), "%s\n", authenticate_user(username, password) ? "LOGIN_OK" : "LOGIN_FAIL");
        } else {
            snprintf(response, sizeof(response), "INVALID_COMMAND\n");
        }
    } else {
        snprintf(response, sizeof(response), "INVALID_COMMAND\n");
    }

    send(sock, response, strlen(response), 0);
    close(sock);
    return NULL;
}

void* run_server(void* arg) {
    (void)arg;
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 5);

    printf("Server listening on port %d\n", PORT);

    while (server_running) {
        new_socket = accept(server_fd, NULL, NULL);
        if (new_socket < 0) {
            if(server_running) perror("accept");
            continue;
        }

        int *client_sock = malloc(sizeof(int));
        *client_sock = new_socket;

        pthread_t client_thread;
        pthread_create(&client_thread, NULL, handle_client, (void*)client_sock);
        pthread_detach(client_thread);
    }

    close(server_fd);
    printf("Server stopped.\n");
    return NULL;
}

char* send_request(const char *request) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        char *error_msg = strdup("ERROR: Connection Failed");
        close(sock);
        return error_msg;
    }

    char full_request[BUFFER_SIZE];
    snprintf(full_request, sizeof(full_request), "%s\n", request);

    send(sock, full_request, strlen(full_request), 0);

    static char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    read(sock, buffer, BUFFER_SIZE - 1);

    // Trim newline
    buffer[strcspn(buffer, "\r\n")] = 0;

    close(sock);
    return buffer;
}


int main() {
    pthread_t server_thread;
    pthread_create(&server_thread, NULL, run_server, NULL);

    struct timespec ts = {0, 500000000L}; // 500ms
    nanosleep(&ts, NULL);

    printf("--- Test Cases ---\n");

    // Test 1
    printf("Test 1: Register user 'testuser1'\n");
    printf("Server response: %s\n", send_request("REGISTER testuser1 StrongPass123!"));

    // Test 2
    printf("\nTest 2: Login with 'testuser1' (correct password)\n");
    printf("Server response: %s\n", send_request("LOGIN testuser1 StrongPass123!"));

    // Test 3
    printf("\nTest 3: Login with 'testuser1' (wrong password)\n");
    printf("Server response: %s\n", send_request("LOGIN testuser1 WrongPassword"));

    // Test 4
    printf("\nTest 4: Login with 'no_such_user'\n");
    printf("Server response: %s\n", send_request("LOGIN no_such_user some_password"));

    // Test 5
    printf("\nTest 5: Register and login 'testuser2'\n");
    printf("Server response (Register): %s\n", send_request("REGISTER testuser2 AnotherSecurePass$"));
    printf("Server response (Login): %s\n", send_request("LOGIN testuser2 AnotherSecurePass$"));

    printf("\n--- Tests Complete ---\n");

    server_running = false;

    // Dummy connection to unblock accept()
    int shutdown_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(shutdown_sock >= 0) {
        struct sockaddr_in serv_addr;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);
        inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
        connect(shutdown_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        close(shutdown_sock);
    }
    
    pthread_join(server_thread, NULL);
    remove(USER_DB_FILE);
    
    return 0;
}