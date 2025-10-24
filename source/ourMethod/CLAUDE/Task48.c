
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>

/* Maximum message size to prevent unbounded memory allocation */
#define MAX_MESSAGE_SIZE 4096
/* Maximum number of clients to prevent resource exhaustion */
#define MAX_CLIENTS 100
/* Server port */
#define SERVER_PORT 8888

/* Client information structure */
typedef struct {
    int fd;
    int active;
} client_info_t;

/* Server context structure */
typedef struct {
    int server_fd;
    client_info_t clients[MAX_CLIENTS];
    pthread_mutex_t clients_mutex;
    volatile sig_atomic_t running;
} server_context_t;

/* Thread argument for client handler */
typedef struct {
    server_context_t *server;
    int client_fd;
} client_thread_arg_t;

/* Initialize server context */
static int init_server_context(server_context_t *ctx) {
    if (ctx == NULL) {
        return -1;
    }
    
    ctx->server_fd = -1;
    ctx->running = 0;
    
    /* Initialize all client slots as inactive */
    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        ctx->clients[i].fd = -1;
        ctx->clients[i].active = 0;
    }
    
    /* Initialize mutex with error checking */
    if (pthread_mutex_init(&ctx->clients_mutex, NULL) != 0) {
        return -1;
    }
    
    return 0;
}

/* Cleanup server context */
static void cleanup_server_context(server_context_t *ctx) {
    if (ctx == NULL) {
        return;
    }
    
    ctx->running = 0;
    
    if (ctx->server_fd >= 0) {
        close(ctx->server_fd);
        ctx->server_fd = -1;
    }
    
    /* Close all client connections */
    pthread_mutex_lock(&ctx->clients_mutex);
    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (ctx->clients[i].active && ctx->clients[i].fd >= 0) {
            close(ctx->clients[i].fd);
            ctx->clients[i].fd = -1;
            ctx->clients[i].active = 0;
        }
    }
    pthread_mutex_unlock(&ctx->clients_mutex);
    
    pthread_mutex_destroy(&ctx->clients_mutex);
}

/* Add client to server with bounds checking */
static int add_client(server_context_t *ctx, int client_fd) {
    if (ctx == NULL || client_fd < 0) {
        return -1;
    }
    
    pthread_mutex_lock(&ctx->clients_mutex);
    
    int slot = -1;
    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (!ctx->clients[i].active) {
            slot = (int)i;
            break;
        }
    }
    
    if (slot >= 0) {
        ctx->clients[slot].fd = client_fd;
        ctx->clients[slot].active = 1;
    }
    
    pthread_mutex_unlock(&ctx->clients_mutex);
    
    return slot;
}

/* Remove client from server */
static void remove_client(server_context_t *ctx, int client_fd) {
    if (ctx == NULL || client_fd < 0) {
        return;
    }
    
    pthread_mutex_lock(&ctx->clients_mutex);
    
    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (ctx->clients[i].active && ctx->clients[i].fd == client_fd) {
            close(ctx->clients[i].fd);
            ctx->clients[i].fd = -1;
            ctx->clients[i].active = 0;
            break;
        }
    }
    
    pthread_mutex_unlock(&ctx->clients_mutex);
}

/* Broadcast message to all clients except sender */
static void broadcast_message(server_context_t *ctx, const char *message, size_t msg_len, int sender_fd) {
    if (ctx == NULL || message == NULL || msg_len == 0 || msg_len > MAX_MESSAGE_SIZE) {
        return;
    }
    
    pthread_mutex_lock(&ctx->clients_mutex);
    
    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (ctx->clients[i].active && ctx->clients[i].fd != sender_fd) {
            /* Use send with error checking */
            ssize_t sent = send(ctx->clients[i].fd, message, msg_len, MSG_NOSIGNAL);
            if (sent < 0) {
                fprintf(stderr, "Send error to client %d\\n", ctx->clients[i].fd);
            }
        }
    }
    
    pthread_mutex_unlock(&ctx->clients_mutex);
}
/* Client handler thread */
static void* handle_client_thread(void* arg) {
    if (arg == NULL) {
        return NULL;
    }

    client_thread_arg_t* thread_arg = (client_thread_arg_t*)arg;
    server_context_t* server = thread_arg->server;
    int client_fd = thread_arg->client_fd;

    /* Free argument as we've copied needed data */
    free(thread_arg);
    thread_arg = NULL;

    /* Allocate buffer on heap with size validation */
    char* buffer = (char*)calloc(MAX_MESSAGE_SIZE + 1, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed for client buffer\n");
        remove_client(server, client_fd);
        return NULL;
    }

    while (server->running) {
        /* Clear buffer for security - use memset_s if available, otherwise memset */
        memset(buffer, 0, MAX_MESSAGE_SIZE + 1);

        /* Read with size limit to prevent buffer overflow */
        ssize_t bytes_read = recv(client_fd, buffer, MAX_MESSAGE_SIZE, 0);

        if (bytes_read <= 0) {
            /* Client disconnected or error */
            break;
        }

        /* Ensure null termination */
        buffer[bytes_read] = '\0';

        /* Validate input: check for embedded nulls (basic sanitization) */
        int valid = 1;
        for (ssize_t i = 0; i < bytes_read; i++) {
            if (buffer[i] == '\0') {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            fprintf(stderr, "Invalid message format from client %d\n", client_fd);
            continue;
        }

        /* Broadcast to other clients */
        broadcast_message(server, buffer, (size_t)bytes_read, client_fd);
    }

    /* Clear sensitive data before freeing */
    memset(buffer, 0, MAX_MESSAGE_SIZE + 1);
    free(buffer);
    buffer = NULL;

    remove_client(server, client_fd);
    return NULL;
}

/* Start server */
static int start_server(server_context_t* ctx) {
    if (ctx == NULL) {
        return -1;
    }

    /* Create socket */
    ctx->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (ctx->server_fd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    /* Set socket options to reuse address */
    int opt = 1;
    if (setsockopt(ctx->server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("Setsockopt failed");
        close(ctx->server_fd);
        ctx->server_fd = -1;
        return -1;
    }

    /* Bind to address */
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(SERVER_PORT);

    if (bind(ctx->server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(ctx->server_fd);
        ctx->server_fd = -1;
        return -1;
    }

    /* Listen with bounded backlog */
    if (listen(ctx->server_fd, 10) < 0) {
        perror("Listen failed");
        close(ctx->server_fd);
        ctx->server_fd = -1;
        return -1;
    }

    ctx->running = 1;
    printf("Server started on port %d\n", SERVER_PORT);

    /* Accept clients in loop */
    while (ctx->running) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        memset(&client_addr, 0, sizeof(client_addr));

        int client_fd = accept(ctx->server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd < 0) {
            if (ctx->running) {
                perror("Accept failed");
            }
            continue;
        }

        /* Check client limit before adding */
        int slot = add_client(ctx, client_fd);
        if (slot < 0) {
            fprintf(stderr, "Max clients reached, rejecting connection\n");
            close(client_fd);
            continue;
        }

        printf("Client connected: %d\n", client_fd);

        /* Prepare thread argument */
        client_thread_arg_t* arg = (client_thread_arg_t*)malloc(sizeof(client_thread_arg_t));
        if (arg == NULL) {
            fprintf(stderr, "Memory allocation failed for thread arg\n");
            remove_client(ctx, client_fd);
            continue;
        }

        arg->server = ctx;
        arg->client_fd = client_fd;

        /* Handle client in separate thread */
        pthread_t client_thread;
        if (pthread_create(&client_thread, NULL, handle_client_thread, arg) != 0) {
            fprintf(stderr, "Thread creation failed\n");
            free(arg);
            remove_client(ctx, client_fd);
            continue;
        }

        pthread_detach(client_thread);
    }

    return 0;
}

/* Simple client structure */
typedef struct {
    int sock_fd;
    volatile sig_atomic_t running;
} client_context_t;

/* Initialize client context */
static int init_client_context(client_context_t* ctx) {
    if (ctx == NULL) {
        return -1;
    }

    ctx->sock_fd = -1;
    ctx->running = 0;
    return 0;
}

/* Connect client to server */
static int connect_to_server(client_context_t* ctx, const char* host, int port) {
    if (ctx == NULL || host == NULL) {
        return -1;
    }

    /* Validate port range */
    if (port <= 0 || port > 65535) {
        fprintf(stderr, "Invalid port number\n");
        return -1;
    }

    ctx->sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (ctx->sock_fd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons((uint16_t)port);

    /* Convert address with validation */
    if (inet_pton(AF_INET, host, &server_addr.sin_addr) <= 0) {
        fprintf(stderr, "Invalid address\n");
        close(ctx->sock_fd);
        ctx->sock_fd = -1;
        return -1;
    }

    if (connect(ctx->sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(ctx->sock_fd);
        ctx->sock_fd = -1;
        return -1;
    }

    ctx->running = 1;
    return 0;
}

/* Send message from client */
static void send_message(client_context_t* ctx, const char* message, size_t msg_len) {
    if (ctx == NULL || message == NULL || ctx->sock_fd < 0 || !ctx->running) {
        return;
    }

    /* Validate message length */
    if (msg_len == 0 || msg_len > MAX_MESSAGE_SIZE) {
        fprintf(stderr, "Invalid message length\n");
        return;
    }

    ssize_t sent = send(ctx->sock_fd, message, msg_len, MSG_NOSIGNAL);
    if (sent < 0) {
        perror("Send failed");
    }
}

/* Disconnect client */
static void disconnect_client(client_context_t* ctx) {
    if (ctx == NULL) {
        return;
    }

    ctx->running = 0;
    if (ctx->sock_fd >= 0) {
        close(ctx->sock_fd);
        ctx->sock_fd = -1;
    }
}

int main(void) {
    printf("Simple Chat Application\n");
    printf("1. Run as server\n");
    printf("2. Run as client\n");

    int choice = 0;
    printf("Enter choice (1 or 2): ");
    if (scanf("%d", &choice) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    getchar(); /* Clear newline */

    if (choice == 1) {
        /* Test Case 1: Start server */
        server_context_t server;
        if (init_server_context(&server) != 0) {
            fprintf(stderr, "Failed to initialize server\n");
            return 1;
        }

        printf("Starting server...\n");

        /* Run server (blocking) */
        start_server(&server);

        cleanup_server_context(&server);
    } else if (choice == 2) {
        /* Test Cases 2-5: Client operations */
        client_context_t client;
        if (init_client_context(&client) != 0) {
            fprintf(stderr, "Failed to initialize client\n");
            return 1;
        }

        /* Test Case 2: Connect to server */
        printf("Connecting to 127.0.0.1:%d\n", SERVER_PORT);
        if (connect_to_server(&client, "127.0.0.1", SERVER_PORT) != 0) {
            fprintf(stderr, "Failed to connect\n");
            return 1;
        }

        printf("Connected! Type messages (empty line to quit)\n");

        /* Test Cases 3-5: Send messages */
        char* line = NULL;
        size_t line_cap = 0;
        ssize_t line_len;

        while (client.running) {
            line_len = getline(&line, &line_cap, stdin);
            if (line_len <= 0) {
                break;
            }

            /* Remove newline if present */
            if (line_len > 0 && line[line_len - 1] == '\n') {
                line[line_len - 1] = '\0';
                line_len--;
            }

            if (line_len == 0) {
                break;
            }

            send_message(&client, line, (size_t)line_len);
        }

        /* Clear and free line buffer */
        if (line != NULL) {
            memset(line, 0, line_cap);
            free(line);
            line = NULL;
        }

        disconnect_client(&client);
    } else {
        fprintf(stderr, "Invalid choice\n");
        return 1;
    }

    return 0;
}
