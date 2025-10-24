#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>

#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 128
#define MIN_PASSWORD_LEN 8
#define SALT_LEN 16
#define HASH_LEN 32
#define BUFFER_SIZE 4096
#define MAX_PATH_LEN 256
#define PBKDF2_ITERATIONS 210000

/* Security: Constant-time comparison to prevent timing attacks */
int constant_time_compare(const char *a, const char *b, size_t len) {
    if (a == NULL || b == NULL) return 0;
    volatile unsigned char result = 0;
    for (size_t i = 0; i < len; i++) {
        result |= (unsigned char)a[i] ^ (unsigned char)b[i];
    }
    return result == 0;
}

/* Security: Generate cryptographically secure random salt */
int generate_salt(unsigned char *salt, size_t length) {
    if (salt == NULL || length == 0) return 0;
    /* Security: Use OpenSSL's secure random generator */
    if (RAND_bytes(salt, (int)length) != 1) {
        return 0;
    }
    return 1;
}

/* Security: Convert binary to hex string with bounds checking */
int bin_to_hex(const unsigned char *bin, size_t bin_len, char *hex, size_t hex_size) {
    if (bin == NULL || hex == NULL) return 0;
    /* Security: Check buffer size */
    if (hex_size < bin_len * 2 + 1) return 0;

    for (size_t i = 0; i < bin_len; i++) {
        /* Security: Use snprintf with bounds checking */
        if (snprintf(hex + i * 2, 3, "%02x", bin[i]) != 2) {
            return 0;
        }
    }
    hex[bin_len * 2] = '\0';
    return 1;
}

/* Security: Convert hex string to binary with validation */
int hex_to_bin(const char *hex, unsigned char *bin, size_t bin_size) {
    if (hex == NULL || bin == NULL) return 0;
    size_t hex_len = strlen(hex);
    if (hex_len % 2 != 0 || hex_len / 2 > bin_size) return 0;

    for (size_t i = 0; i < hex_len; i += 2) {
        /* Security: Validate hex characters */
        if (!isxdigit((unsigned char)hex[i]) || !isxdigit((unsigned char)hex[i + 1])) return 0;

        char byte_str[3] = { hex[i], hex[i + 1], '\0' };
        bin[i / 2] = (unsigned char)strtol(byte_str, NULL, 16);
    }
    return 1;
}

/* Security: PBKDF2-HMAC-SHA256 with at least 210000 iterations */
int pbkdf2_hash(const char *password, const unsigned char *salt, size_t salt_len,
                unsigned char *hash, size_t hash_len) {
    if (password == NULL || salt == NULL || hash == NULL) return 0;

    /* Security: Use PBKDF2 with SHA256 and high iteration count */
    if (PKCS5_PBKDF2_HMAC(password, (int)strlen(password),
                          salt, (int)salt_len,
                          PBKDF2_ITERATIONS,
                          EVP_sha256(),
                          (int)hash_len, hash) != 1) {
        return 0;
    }
    return 1;
}

/* Security: Validate username - alphanumeric and underscore only */
int validate_username(const char *username) {
    if (username == NULL) return 0;
    size_t len = strlen(username);
    if (len == 0 || len > MAX_USERNAME_LEN) return 0;

    /* Security: Check each character */
    for (size_t i = 0; i < len; i++) {
        if (!isalnum((unsigned char)username[i]) && username[i] != '_') {
            return 0;
        }
    }
    return 1;
}

/* Security: Validate password length and complexity */
int validate_password(const char *password) {
    if (password == NULL) return 0;
    size_t len = strlen(password);
    /* Security: Enforce password policy */
    if (len < MIN_PASSWORD_LEN || len > MAX_PASSWORD_LEN) return 0;
    return 1;
}

/* Security: Sanitize path to prevent directory traversal */
int sanitize_path(const char *base_dir, const char *filename, char *output, size_t output_size) {
    if (base_dir == NULL || filename == NULL || output == NULL) return 0;

    /* Security: Reject path traversal attempts */
    if (strstr(filename, "..") != NULL ||
        strchr(filename, '/') != NULL ||
        strchr(filename, '\\') != NULL) {
        return 0;
    }

    /* Security: Construct safe path with bounds checking */
    int written = snprintf(output, output_size, "%s/%s", base_dir, filename);
    if (written < 0 || (size_t)written >= output_size) {
        return 0;
    }
    return 1;
}

/* Security: Store user credentials with salt and hash */
int store_user(const char *users_dir, const char *username, const char *password) {
    if (users_dir == NULL || username == NULL || password == NULL) return 0;

    /* Security: Validate inputs */
    if (!validate_username(username) || !validate_password(password)) {
        return 0;
    }

    unsigned char salt[SALT_LEN];
    unsigned char hash[HASH_LEN];
    char salt_hex[SALT_LEN * 2 + 1];
    char hash_hex[HASH_LEN * 2 + 1];

    /* Security: Generate random salt */
    if (!generate_salt(salt, SALT_LEN)) {
        return 0;
    }

    /* Security: Derive key using PBKDF2 */
    if (!pbkdf2_hash(password, salt, SALT_LEN, hash, HASH_LEN)) {
        /* Security: Clear sensitive data on error */
        OPENSSL_cleanse(salt, SALT_LEN);
        OPENSSL_cleanse(hash, HASH_LEN);
        return 0;
    }

    /* Security: Convert to hex for storage */
    if (!bin_to_hex(salt, SALT_LEN, salt_hex, sizeof(salt_hex)) ||
        !bin_to_hex(hash, HASH_LEN, hash_hex, sizeof(hash_hex))) {
        OPENSSL_cleanse(salt, SALT_LEN);
        OPENSSL_cleanse(hash, HASH_LEN);
        return 0;
    }

    char user_file[MAX_PATH_LEN];
    char temp_file[MAX_PATH_LEN];

    /* Security: Build safe filename */
    if (snprintf(user_file, sizeof(user_file), "%s.dat", username) >= (int)sizeof(user_file)) {
        OPENSSL_cleanse(salt, SALT_LEN);
        OPENSSL_cleanse(hash, HASH_LEN);
        return 0;
    }

    char safe_path[MAX_PATH_LEN];
    if (!sanitize_path(users_dir, user_file, safe_path, sizeof(safe_path))) {
        OPENSSL_cleanse(salt, SALT_LEN);
        OPENSSL_cleanse(hash, HASH_LEN);
        return 0;
    }

    /* Security: Write to temp file first (TOCTOU mitigation) */
    if (snprintf(temp_file, sizeof(temp_file), "%s.tmp", safe_path) >= (int)sizeof(temp_file)) {
        OPENSSL_cleanse(salt, SALT_LEN);
        OPENSSL_cleanse(hash, HASH_LEN);
        return 0;
    }

    /* Security: Use "w" to create temp file then atomically rename */
    FILE *fp = fopen(temp_file, "w");
    if (fp == NULL) {
        OPENSSL_cleanse(salt, SALT_LEN);
        OPENSSL_cleanse(hash, HASH_LEN);
        return 0;
    }

    /* Security: Write salt and hash */
    if (fprintf(fp, "%s\n%s\n", salt_hex, hash_hex) < 0) {
        fclose(fp);
        unlink(temp_file);
        OPENSSL_cleanse(salt, SALT_LEN);
        OPENSSL_cleanse(hash, HASH_LEN);
        return 0;
    }

    /* Security: Flush and close */
    if (fflush(fp) != 0 || fclose(fp) != 0) {
        unlink(temp_file);
        OPENSSL_cleanse(salt, SALT_LEN);
        OPENSSL_cleanse(hash, HASH_LEN);
        return 0;
    }

    /* Security: Atomic rename */
    if (rename(temp_file, safe_path) != 0) {
        unlink(temp_file);
        OPENSSL_cleanse(salt, SALT_LEN);
        OPENSSL_cleanse(hash, HASH_LEN);
        return 0;
    }

    /* Security: Clear sensitive data */
    OPENSSL_cleanse(salt, SALT_LEN);
    OPENSSL_cleanse(hash, HASH_LEN);

    return 1;
}

/* Security: Authenticate user with constant-time comparison */
int authenticate_user(const char *users_dir, const char *username, const char *password) {
    if (users_dir == NULL || username == NULL || password == NULL) return 0;

    /* Security: Validate inputs */
    if (!validate_username(username) || !validate_password(password)) {
        return 0;
    }

    char user_file[MAX_PATH_LEN];
    if (snprintf(user_file, sizeof(user_file), "%s.dat", username) >= (int)sizeof(user_file)) {
        return 0;
    }

    char safe_path[MAX_PATH_LEN];
    if (!sanitize_path(users_dir, user_file, safe_path, sizeof(safe_path))) {
        return 0;
    }

    FILE *fp = fopen(safe_path, "r");
    if (fp == NULL) {
        return 0;
    }

    char stored_salt_hex[SALT_LEN * 2 + 2];
    char stored_hash_hex[HASH_LEN * 2 + 2];

    /* Security: Read with bounds checking using fgets */
    if (fgets(stored_salt_hex, sizeof(stored_salt_hex), fp) == NULL ||
        fgets(stored_hash_hex, sizeof(stored_hash_hex), fp) == NULL) {
        fclose(fp);
        return 0;
    }
    fclose(fp);

    /* Security: Remove newlines */
    stored_salt_hex[strcspn(stored_salt_hex, "\n")] = '\0';
    stored_hash_hex[strcspn(stored_hash_hex, "\n")] = '\0';

    /* Security: Validate hex string lengths */
    if (strlen(stored_salt_hex) != SALT_LEN * 2 ||
        strlen(stored_hash_hex) != HASH_LEN * 2) {
        return 0;
    }

    unsigned char stored_salt[SALT_LEN];
    unsigned char computed_hash[HASH_LEN];
    unsigned char stored_hash[HASH_LEN];

    /* Security: Convert hex to binary */
    if (!hex_to_bin(stored_salt_hex, stored_salt, SALT_LEN) ||
        !hex_to_bin(stored_hash_hex, stored_hash, HASH_LEN)) {
        return 0;
    }

    /* Security: Compute hash of provided password */
    if (!pbkdf2_hash(password, stored_salt, SALT_LEN, computed_hash, HASH_LEN)) {
        OPENSSL_cleanse(computed_hash, HASH_LEN);
        return 0;
    }

    /* Security: Constant-time comparison */
    int result = constant_time_compare((const char *)computed_hash,
                                       (const char *)stored_hash, HASH_LEN);

    /* Security: Clear sensitive data */
    OPENSSL_cleanse(computed_hash, HASH_LEN);
    OPENSSL_cleanse(stored_salt, SALT_LEN);
    OPENSSL_cleanse(stored_hash, HASH_LEN);

    return result;
}

/* Security: Parse message with validation */
int parse_message(const char *msg, char *cmd, char *username, char *password,
                  size_t cmd_size, size_t user_size, size_t pass_size) {
    if (msg == NULL || cmd == NULL || username == NULL || password == NULL) return 0;

    /* Security: Check message length */
    size_t msg_len = strlen(msg);
    if (msg_len == 0 || msg_len > BUFFER_SIZE) return 0;

    /* Security: Initialize outputs */
    cmd[0] = '\0';
    username[0] = '\0';
    password[0] = '\0';

    /* Security: Parse with bounds checking */
    const char *line = msg;
    const char *next_line;

    /* Parse command */
    if (strncmp(line, "CMD: ", 5) != 0) return 0;
    next_line = strchr(line, '\n');
    if (next_line == NULL) return 0;

    size_t cmd_len = (size_t)(next_line - line - 5);
    if (cmd_len >= cmd_size) return 0;
    memcpy(cmd, line + 5, cmd_len);
    cmd[cmd_len] = '\0';

    line = next_line + 1;

    /* Parse username */
    if (strncmp(line, "USERNAME: ", 10) != 0) return 0;
    next_line = strchr(line, '\n');
    if (next_line == NULL) return 0;

    size_t user_len = (size_t)(next_line - line - 10);
    if (user_len >= user_size) return 0;
    memcpy(username, line + 10, user_len);
    username[user_len] = '\0';

    line = next_line + 1;

    /* Parse password */
    if (strncmp(line, "PASSWORD: ", 10) != 0) return 0;
    next_line = strchr(line, '\n');
    if (next_line != NULL) {
        size_t pass_len = (size_t)(next_line - line - 10);
        if (pass_len >= pass_size) return 0;
        memcpy(password, line + 10, pass_len);
        password[pass_len] = '\0';
    } else {
        size_t pass_len = strlen(line + 10);
        if (pass_len >= pass_size) return 0;
        memcpy(password, line + 10, pass_len);
        password[pass_len] = '\0';
    }

    /* Security: Validate parsed fields */
    if (!validate_username(username) || !validate_password(password)) {
        return 0;
    }

    return 1;
}

/* Security: Handle client request with validation */
int handle_request(const char *users_dir, const char *request, char *response, size_t response_size) {
    if (users_dir == NULL || request == NULL || response == NULL) return 0;

    char cmd[64];
    char username[MAX_USERNAME_LEN + 1];
    char password[MAX_PASSWORD_LEN + 1];

    /* Security: Parse and validate request */
    if (!parse_message(request, cmd, username, password,
                       sizeof(cmd), sizeof(username), sizeof(password))) {
        snprintf(response, response_size, "ERROR: Invalid request format\n");
        return 1;
    }

    /* Security: Process commands */
    if (strcmp(cmd, "LOGIN") == 0) {
        if (authenticate_user(users_dir, username, password)) {
            snprintf(response, response_size, "SUCCESS: Login successful\n");
        } else {
            snprintf(response, response_size, "ERROR: Authentication failed\n");
        }
    } else if (strcmp(cmd, "REGISTER") == 0) {
        if (store_user(users_dir, username, password)) {
            snprintf(response, response_size, "SUCCESS: Registration successful\n");
        } else {
            snprintf(response, response_size, "ERROR: Registration failed\n");
        }
    } else {
        snprintf(response, response_size, "ERROR: Unknown command\n");
    }

    /* Security: Clear sensitive data */
    OPENSSL_cleanse(password, sizeof(password));

    return 1;
}

/* Server functions */
int start_server(int port) {
    /* Security: Create socket with error checking */
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket failed");
        return -1;
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        close(server_fd);
        return -1;
    }

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons((uint16_t)port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        return -1;
    }

    if (listen(server_fd, 5) < 0) {
        perror("listen failed");
        close(server_fd);
        return -1;
    }

    return server_fd;
}

void run_server(int server_fd, const char *users_dir) {
    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_fd < 0) {
            continue;
        }

        /* Security: Allocate buffer with bounds checking */
        char *buffer = calloc(BUFFER_SIZE, 1);
        if (buffer == NULL) {
            close(client_fd);
            continue;
        }

        ssize_t bytes_read = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';

            char *response = calloc(BUFFER_SIZE, 1);
            if (response != NULL) {
                handle_request(users_dir, buffer, response, BUFFER_SIZE);
                send(client_fd, response, strlen(response), 0);
                free(response);
            }
        }

        free(buffer);
        close(client_fd);
    }
}

/* Client functions */
int connect_to_server(const char *host, int port) {
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        return -1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons((uint16_t)port);

    if (inet_pton(AF_INET, host, &server_addr.sin_addr) <= 0) {
        close(sock_fd);
        return -1;
    }

    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        close(sock_fd);
        return -1;
    }

    return sock_fd;
}

int send_request(int sock_fd, const char *cmd, const char *username, const char *password,
                 char *response, size_t response_size) {
    if (sock_fd < 0 || cmd == NULL || username == NULL || password == NULL || response == NULL) {
        return 0;
    }

    /* Security: Validate inputs */
    if (!validate_username(username) || !validate_password(password)) {
        snprintf(response, response_size, "ERROR: Invalid credentials format\n");
        return 0;
    }

    /* Security: Construct message with bounds checking */
    char *message = calloc(BUFFER_SIZE, 1);
    if (message == NULL) {
        snprintf(response, response_size, "ERROR: Memory allocation failed\n");
        return 0;
    }

    int written = snprintf(message, BUFFER_SIZE,
                           "CMD: %s\nUSERNAME: %s\nPASSWORD: %s\n",
                           cmd, username, password);
    if (written < 0 || written >= BUFFER_SIZE) {
        free(message);
        snprintf(response, response_size, "ERROR: Message construction failed\n");
        return 0;
    }

    if (send(sock_fd, message, strlen(message), 0) < 0) {
        free(message);
        snprintf(response, response_size, "ERROR: Failed to send request\n");
        return 0;
    }

    /* Security: Clear sensitive data */
    OPENSSL_cleanse(message, BUFFER_SIZE);
    free(message);

    /* Security: Receive response with bounds checking */
    ssize_t bytes_read = recv(sock_fd, response, response_size - 1, 0);
    if (bytes_read <= 0) {
        snprintf(response, response_size, "ERROR: Failed to receive response\n");
        return 0;
    }

    response[bytes_read] = '\0';
    return 1;
}

int main(void) {
    printf("=== Secure Chat System Test ===\n");

    /* Test case 1: Server initialization */
    printf("\nTest 1: Server initialization\n");
    int server_fd = start_server(8080);
    if (server_fd < 0) {
        fprintf(stderr, "Failed to start server\n");
        return 1;
    }
    printf("Server started on port 8080\n");

    /* For testing purposes, we'll simulate client-server interaction */
    /* In production, server would run in a separate process/thread */

    /* Test case 2: User registration */
    printf("\nTest 2: User registration\n");
    char response[BUFFER_SIZE];
    const char *test_request = "CMD: REGISTER\nUSERNAME: testuser1\nPASSWORD: SecurePass123!\n";
    handle_request("./users_data", test_request, response, sizeof(response));
    printf("Registration response: %s", response);

    /* Test case 3: User login (valid) */
    printf("\nTest 3: User login (valid credentials)\n");
    const char *login_request = "CMD: LOGIN\nUSERNAME: testuser1\nPASSWORD: SecurePass123!\n";
    handle_request("./users_data", login_request, response, sizeof(response));
    printf("Login response: %s", response);

    /* Test case 4: User login (invalid) */
    printf("\nTest 4: User login (invalid credentials)\n");
    const char *bad_login = "CMD: LOGIN\nUSERNAME: testuser1\nPASSWORD: WrongPassword\n";
    handle_request("./users_data", bad_login, response, sizeof(response));
    printf("Login response: %s", response);

    /* Test case 5: Input validation */
    printf("\nTest 5: Input validation (path traversal attempt)\n");
    const char *malicious_request = "CMD: LOGIN\nUSERNAME: ../../../etc/passwd\nPASSWORD: test1234\n";
    handle_request("./users_data", malicious_request, response, sizeof(response));
    printf("Validation response: %s", response);

    close(server_fd);
    return 0;
}
