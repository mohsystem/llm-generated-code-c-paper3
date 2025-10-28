#include <mongoose.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

// Note: This code requires the civetweb library.
// You need to have civetweb.h and civetweb.c in your project.
// Compile on Linux/macOS: gcc your_file.c civetweb.c -o server -lpthread -ldl
// Compile on Windows: cl your_file.c civetweb.c /link /out:server.exe ws2_32.lib

typedef struct {
    char *username;
    char *text;
} Message;

static Message *messages = NULL;
static size_t message_count = 0;
static size_t message_capacity = 0;

#ifdef _WIN32
static CRITICAL_SECTION messages_mutex;
#else
static pthread_mutex_t messages_mutex = PTHREAD_MUTEX_INITIALIZER;
#endif

#define MAX_USERNAME_LENGTH 50
#define MAX_MESSAGE_LENGTH 280

static void initialize_mutex() {
#ifdef _WIN32
    InitializeCriticalSection(&messages_mutex);
#endif
}

static void lock_mutex() {
#ifdef _WIN32
    EnterCriticalSection(&messages_mutex);
#else
    pthread_mutex_lock(&messages_mutex);
#endif
}

static void unlock_mutex() {
#ifdef _WIN32
    LeaveCriticalSection(&messages_mutex);
#else
    pthread_mutex_unlock(&messages_mutex);
#endif
}

char* escapeHtml(const char* input) {
    if (!input) return NULL;
    size_t input_len = strlen(input);
    size_t worst_case_len = input_len * 5 + 1;
    char* escaped = (char*)malloc(worst_case_len);
    if (!escaped) return NULL;

    char* p = escaped;
    for (size_t i = 0; i < input_len; ++i) {
        switch (input[i]) {
            case '&':  p += sprintf(p, "&amp;");   break;
            case '<':  p += sprintf(p, "&lt;");    break;
            case '>':  p += sprintf(p, "&gt;");    break;
            case '"':  p += sprintf(p, "&quot;");  break;
            case '\'': p += sprintf(p, "&#x27;");  break;
            default:   *p++ = input[i];            break;
        }
    }
    *p = '\0';
    return escaped;
}

int insert_user_message_in_db(const char* username, const char* message_text) {
    if (!username || !message_text) return -1;
    
    lock_mutex();
    if (message_count >= message_capacity) {
        size_t new_capacity = (message_capacity == 0) ? 10 : message_capacity * 2;
        Message *new_messages = (Message*)realloc(messages, new_capacity * sizeof(Message));
        if (!new_messages) {
            unlock_mutex(); return -1;
        }
        messages = new_messages;
        message_capacity = new_capacity;
    }
#ifdef _WIN32
    messages[message_count].username = _strdup(username);
    messages[message_count].text = _strdup(message_text);
#else
    messages[message_count].username = strdup(username);
    messages[message_count].text = strdup(message_text);
#endif
    if (!messages[message_count].username || !messages[message_count].text) {
        free(messages[message_count].username);
        free(messages[message_count].text);
        unlock_mutex(); return -1;
    }
    message_count++;
    unlock_mutex();
    return 0;
}

void cleanup() {
    lock_mutex();
    for (size_t i = 0; i < message_count; ++i) {
        free(messages[i].username);
        free(messages[i].text);
    }
    free(messages);
    unlock_mutex();
#ifndef _WIN32
    pthread_mutex_destroy(&messages_mutex);
#endif
}

int main(void) {
    initialize_mutex();
    
    insert_user_message_in_db("Alice", "Hello from C and Civetweb!");
    insert_user_message_in_db("Bob", "This is a test message.");
    insert_user_message_in_db("Charlie", "Memory is managed manually.");
    insert_user_message_in_db("David", "Mutexes for thread safety are important.");
    insert_user_message_in_db("Eve", "<script>alert('I am escaped!')</script>");

    const char *options[] = {"listening_ports", "8080", "num_threads", "4", NULL};

    printf("Server stopped.\n");
    cleanup();
    return 0;
}