#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#include <openssl/rand.h>
#include <openssl/err.h>

// Compile with: gcc your_file_name.c -o your_executable -lssl -lcrypto -pthread

#define SESSION_ID_BYTES 32
#define SESSION_ID_HEX_LEN (SESSION_ID_BYTES * 2 + 1)

typedef struct SessionNode {
    char session_id[SESSION_ID_HEX_LEN];
    char* username;
    time_t creation_time;
    struct SessionNode* next;
} SessionNode;

typedef struct {
    SessionNode* head;
    long session_timeout_seconds;
    pthread_mutex_t lock;
} SessionManager;

// Utility to create and initialize the manager
SessionManager* session_manager_create(long timeout_seconds) {
    if (timeout_seconds <= 0) {
        fprintf(stderr, "Session timeout must be positive.\n");
        return NULL;
    }
    SessionManager* manager = (SessionManager*)malloc(sizeof(SessionManager));
    if (!manager) {
        perror("Failed to allocate SessionManager");
        return NULL;
    }
    manager->head = NULL;
    manager->session_timeout_seconds = timeout_seconds;
    if (pthread_mutex_init(&manager->lock, NULL) != 0) {
        perror("Mutex init failed");
        free(manager);
        return NULL;
    }
    return manager;
}

// Utility to clean up and free all resources
void session_manager_destroy(SessionManager* manager) {
    if (!manager) return;
    pthread_mutex_lock(&manager->lock);
    SessionNode* current = manager->head;
    while (current != NULL) {
        SessionNode* next = current->next;
        free(current->username);
        free(current);
        current = next;
    }
    manager->head = NULL;
    pthread_mutex_unlock(&manager->lock);
    pthread_mutex_destroy(&manager->lock);
    free(manager);
}

// Internal function to remove expired sessions. Must be called within a lock.
void remove_expired_sessions_locked(SessionManager* manager) {
    time_t now = time(NULL);
    SessionNode* current = manager->head;
    SessionNode* prev = NULL;

    while (current != NULL) {
        if (now >= current->creation_time + manager->session_timeout_seconds) {
            SessionNode* to_delete = current;
            if (prev == NULL) { // Head is expired
                manager->head = current->next;
                current = manager->head;
            } else {
                prev->next = current->next;
                current = prev->next;
            }
            free(to_delete->username);
            free(to_delete);
        } else {
            prev = current;
            current = current->next;
        }
    }
}


const char* create_session(SessionManager* manager, const char* username) {
    if (!manager || !username || strspn(username, " \t\n\v\f\r") == strlen(username)) {
        return NULL;
    }

    unsigned char random_bytes[SESSION_ID_BYTES];
    if (RAND_bytes(random_bytes, sizeof(random_bytes)) != 1) {
        fprintf(stderr, "OpenSSL RAND_bytes failed: %s\n", ERR_error_string(ERR_get_error(), NULL));
        return NULL;
    }

    SessionNode* new_node = (SessionNode*)malloc(sizeof(SessionNode));
    if (!new_node) {
        perror("Failed to allocate session node");
        return NULL;
    }
    
    for (int i = 0; i < SESSION_ID_BYTES; i++) {
        snprintf(&new_node->session_id[i*2], 3, "%02x", random_bytes[i]);
    }

    new_node->username = strdup(username);
    if (!new_node->username) {
        perror("Failed to duplicate username");
        free(new_node);
        return NULL;
    }

    new_node->creation_time = time(NULL);

    pthread_mutex_lock(&manager->lock);
    remove_expired_sessions_locked(manager); // Clean up before adding new
    new_node->next = manager->head;
    manager->head = new_node;
    pthread_mutex_unlock(&manager->lock);

    return new_node->session_id;
}


int is_valid_session(SessionManager* manager, const char* session_id) {
    if (!manager || !session_id) return 0;
    
    pthread_mutex_lock(&manager->lock);
    remove_expired_sessions_locked(manager);
    
    SessionNode* current = manager->head;
    int found = 0;
    while (current != NULL) {
        if (strncmp(current->session_id, session_id, SESSION_ID_HEX_LEN) == 0) {
            found = 1;
            break;
        }
        current = current->next;
    }
    
    pthread_mutex_unlock(&manager->lock);
    return found;
}


// Returns a dynamically allocated string with the username. Caller must free it.
char* get_session_user(SessionManager* manager, const char* session_id) {
    if (!manager || !session_id) return NULL;

    pthread_mutex_lock(&manager->lock);
    remove_expired_sessions_locked(manager);

    SessionNode* current = manager->head;
    char* username = NULL;
    while (current != NULL) {
        if (strncmp(current->session_id, session_id, SESSION_ID_HEX_LEN) == 0) {
            username = strdup(current->username);
            break;
        }
        current = current->next;
    }
    pthread_mutex_unlock(&manager->lock);
    return username;
}

void end_session(SessionManager* manager, const char* session_id) {
    if (!manager || !session_id) return;

    pthread_mutex_lock(&manager->lock);
    SessionNode* current = manager->head;
    SessionNode* prev = NULL;
    
    while (current != NULL) {
        if (strncmp(current->session_id, session_id, SESSION_ID_HEX_LEN) == 0) {
            if (prev == NULL) {
                manager->head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->username);
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }
    pthread_mutex_unlock(&manager->lock);
}

void sleep_seconds(int seconds) {
    #ifdef _WIN32
        #include <windows.h>
        Sleep(seconds * 1000);
    #else
        #include <unistd.h>
        sleep(seconds);
    #endif
}

int main() {
    // Test case 1: Create and validate a new session
    printf("--- Test Case 1: Create and Validate Session ---\n");
    SessionManager* manager = session_manager_create(1800);
    const char* alice_session_id_ptr = create_session(manager, "alice");
    char alice_session_id[SESSION_ID_HEX_LEN];
    if (alice_session_id_ptr) {
        strncpy(alice_session_id, alice_session_id_ptr, sizeof(alice_session_id) - 1);
        alice_session_id[sizeof(alice_session_id) - 1] = '\0';
        
        printf("Created session for alice: %s\n", alice_session_id);
        printf("Is alice's session valid? %s\n", is_valid_session(manager, alice_session_id) ? "true" : "false");
        char* user = get_session_user(manager, alice_session_id);
        if(user) {
            printf("User for session: %s\n", user);
            free(user);
        }
    } else {
        printf("Failed to create session for alice.\n");
    }
    printf("\n");

    // Test case 2: Validate a non-existent session
    printf("--- Test Case 2: Validate Non-existent Session ---\n");
    const char* fake_session_id = "fakeSessionId12345";
    printf("Is fake session valid? %s\n", is_valid_session(manager, fake_session_id) ? "true" : "false");
    char* fake_user = get_session_user(manager, fake_session_id);
    printf("User for fake session: %s\n", fake_user ? fake_user : "Not found");
    free(fake_user);
    printf("\n");

    // Test case 3: Invalidate a session by ending it
    printf("--- Test Case 3: End Session ---\n");
    const char* bob_session_id_ptr = create_session(manager, "bob");
    char bob_session_id[SESSION_ID_HEX_LEN];
    if (bob_session_id_ptr) {
        strncpy(bob_session_id, bob_session_id_ptr, sizeof(bob_session_id) - 1);
        bob_session_id[sizeof(bob_session_id) - 1] = '\0';

        printf("Created session for bob: %s\n", bob_session_id);
        printf("Is bob's session valid before ending? %s\n", is_valid_session(manager, bob_session_id) ? "true" : "false");
        end_session(manager, bob_session_id);
        printf("Ended bob's session.\n");
        printf("Is bob's session valid after ending? %s\n", is_valid_session(manager, bob_session_id) ? "true" : "false");
    } else {
        printf("Failed to create session for bob.\n");
    }
    printf("\n");
    
    // Test case 4: Session expiration
    printf("--- Test Case 4: Session Expiration ---\n");
    SessionManager* short_lived_manager = session_manager_create(2);
    const char* charlie_session_id_ptr = create_session(short_lived_manager, "charlie");
    char charlie_session_id[SESSION_ID_HEX_LEN];
    if (charlie_session_id_ptr) {
        strncpy(charlie_session_id, charlie_session_id_ptr, sizeof(charlie_session_id) - 1);
        charlie_session_id[sizeof(charlie_session_id) - 1] = '\0';
        
        printf("Created short-lived session for charlie: %s\n", charlie_session_id);
        printf("Is charlie's session valid immediately? %s\n", is_valid_session(short_lived_manager, charlie_session_id) ? "true" : "false");
        printf("Waiting for 3 seconds...\n");
        sleep_seconds(3);
        printf("Is charlie's session valid after 3 seconds? %s\n", is_valid_session(short_lived_manager, charlie_session_id) ? "true" : "false");
    } else {
        printf("Failed to create session for charlie.\n");
    }
    session_manager_destroy(short_lived_manager);
    printf("\n");
    
    // Test case 5: Attempt to create session with invalid username
    printf("--- Test Case 5: Invalid Username ---\n");
    if (create_session(manager, NULL) == NULL) {
        printf("Correctly failed to create session for null username.\n");
    }
    if (create_session(manager, "   ") == NULL) {
        printf("Correctly failed to create session for whitespace username.\n");
    }

    session_manager_destroy(manager);
    return 0;
}