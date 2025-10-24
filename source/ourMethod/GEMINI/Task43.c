// Requires OpenSSL (e.g., libssl-dev package) and uthash.h.
// Download uthash.h and place it in the same directory.
// Compile with: gcc task.c -o task -lssl -lcrypto
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // for sleep()

#include <openssl/rand.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#include "uthash.h"

#define SESSION_ID_BYTES 32
// Base64 encoding size: ceil(n/3)*4
#define SESSION_ID_B64_LEN (((SESSION_ID_BYTES + 2) / 3) * 4)
#define SESSION_LIFETIME_SECONDS (30 * 60)
#define USER_ID_MAX_LEN 64

typedef struct Session {
    char sessionId[SESSION_ID_B64_LEN + 1];
    char userId[USER_ID_MAX_LEN + 1];
    time_t expirationTime;
    UT_hash_handle hh; // makes this structure hashable
} Session;

// Global session store (hash table)
Session *g_sessions = NULL;

// Forward declarations
void cleanup_sessions();

int base64_encode(const unsigned char* input, int length, char** output) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;
    int result = -1;

    b64 = BIO_new(BIO_f_base64());
    if (!b64) return -1;
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

    bio = BIO_new(BIO_s_mem());
    if (!bio) {
        BIO_free_all(b64);
        return -1;
    }

    bio = BIO_push(b64, bio);

    if (BIO_write(bio, input, length) <= 0) {
        BIO_free_all(bio);
        return -1;
    }
    
    if (BIO_flush(bio) != 1) {
        BIO_free_all(bio);
        return -1;
    }

    BIO_get_mem_ptr(bio, &bufferPtr);
    
    // NUL-terminate the string
    *output = (char *)malloc(bufferPtr->length + 1);
    if (*output) {
        memcpy(*output, bufferPtr->data, bufferPtr->length);
        (*output)[bufferPtr->length] = '\0';
        result = 0;
    }

    BIO_free_all(bio);
    return result;
}

int generate_session_id(char* out_buffer, size_t buffer_len) {
    unsigned char random_bytes[SESSION_ID_BYTES];
    if (RAND_bytes(random_bytes, sizeof(random_bytes)) != 1) {
        fprintf(stderr, "Error: Failed to generate random bytes.\n");
        return -1;
    }

    char* b64_string = NULL;
    if (base64_encode(random_bytes, sizeof(random_bytes), &b64_string) != 0) {
        fprintf(stderr, "Error: Failed to Base64 encode session ID.\n");
        return -1;
    }
    
    strncpy(out_buffer, b64_string, buffer_len - 1);
    out_buffer[buffer_len - 1] = '\0';
    free(b64_string);

    return 0;
}

const char* create_session(const char* userId, int lifetime_seconds) {
    if (userId == NULL || strlen(userId) == 0 || strlen(userId) > USER_ID_MAX_LEN) {
        fprintf(stderr, "Error: Invalid user ID.\n");
        return NULL;
    }
    
    Session* s = (Session*)malloc(sizeof(Session));
    if (!s) {
        perror("malloc");
        return NULL;
    }
    memset(s, 0, sizeof(Session));

    if (generate_session_id(s->sessionId, sizeof(s->sessionId)) != 0) {
        free(s);
        return NULL;
    }

    strncpy(s->userId, userId, USER_ID_MAX_LEN);
    s->expirationTime = time(NULL) + lifetime_seconds;
    
    HASH_ADD_STR(g_sessions, sessionId, s);
    
    return s->sessionId;
}

const char* get_user_id_from_session(const char* sessionId) {
    if (sessionId == NULL) return NULL;
    
    Session* s;
    HASH_FIND_STR(g_sessions, sessionId, s);
    
    if (s == NULL) {
        return NULL; // Not found
    }
    
    if (time(NULL) > s->expirationTime) {
        HASH_DEL(g_sessions, s);
        free(s);
        return NULL; // Expired
    }
    
    return s->userId;
}

void terminate_session(const char* sessionId) {
    if (sessionId == NULL) return;

    Session* s;
    HASH_FIND_STR(g_sessions, sessionId, s);
    
    if (s != NULL) {
        HASH_DEL(g_sessions, s);
        free(s);
    }
}

void cleanup_sessions() {
    Session *current_session, *tmp;
    HASH_ITER(hh, g_sessions, current_session, tmp) {
        HASH_DEL(g_sessions, current_session);
        free(current_session);
    }
}

void print_validation(const char* context, const char* userId) {
    if (userId) {
        printf("%sValid, User ID: %s\n", context, userId);
    } else {
        printf("%sInvalid\n", context);
    }
}

int main() {
    atexit(cleanup_sessions);

    printf("--- Test Case 1: Session Creation and Validation ---\n");
    char session_id_1[SESSION_ID_B64_LEN + 1];
    const char* created_id_1 = create_session("user123", SESSION_LIFETIME_SECONDS);
    if (created_id_1) {
        strncpy(session_id_1, created_id_1, sizeof(session_id_1) -1);
        session_id_1[sizeof(session_id_1)-1] = '\0';
        printf("Created session for user123: %s\n", session_id_1);
        print_validation("Session validation: ", get_user_id_from_session(session_id_1));
    }

    printf("\n--- Test Case 2: Validation of Non-Existent Session ---\n");
    const char* fake_session_id = "nonexistent-session-id";
    const char* result_2 = get_user_id_from_session(fake_session_id);
    printf("Validation for fake session '%s': %s\n", fake_session_id, result_2 ? "Valid" : "Invalid");
    
    printf("\n--- Test Case 3: Session Termination ---\n");
    char session_id_3[SESSION_ID_B64_LEN + 1];
    const char* created_id_3 = create_session("user456", SESSION_LIFETIME_SECONDS);
    if (created_id_3) {
        strncpy(session_id_3, created_id_3, sizeof(session_id_3)-1);
        session_id_3[sizeof(session_id_3)-1] = '\0';
        printf("Created session for user456: %s\n", session_id_3);
        terminate_session(session_id_3);
        printf("Terminated session for user456.\n");
        print_validation("Validation after termination: ", get_user_id_from_session(session_id_3));
    }
    
    printf("\n--- Test Case 4: Session Expiration ---\n");
    char session_id_4[SESSION_ID_B64_LEN + 1];
    const char* created_id_4 = create_session("user789", 2); // 2-second lifetime
    if (created_id_4) {
        strncpy(session_id_4, created_id_4, sizeof(session_id_4)-1);
        session_id_4[sizeof(session_id_4)-1] = '\0';
        printf("Created short-lived session for user789: %s\n", session_id_4);
        printf("Waiting for 3 seconds for session to expire...\n");
        sleep(3);
        print_validation("Validation after expiration: ", get_user_id_from_session(session_id_4));
    }

    printf("\n--- Test Case 5: Multiple Concurrent Sessions ---\n");
    char userA_session_id[SESSION_ID_B64_LEN + 1];
    char userB_session_id[SESSION_ID_B64_LEN + 1];
    
    const char* userA_created = create_session("userA", SESSION_LIFETIME_SECONDS);
    const char* userB_created = create_session("userB", SESSION_LIFETIME_SECONDS);
    if (userA_created && userB_created) {
        strncpy(userA_session_id, userA_created, sizeof(userA_session_id)-1);
        userA_session_id[sizeof(userA_session_id)-1] = '\0';

        strncpy(userB_session_id, userB_created, sizeof(userB_session_id)-1);
        userB_session_id[sizeof(userB_session_id)-1] = '\0';

        printf("Created session for userA: %s\n", userA_session_id);
        printf("Created session for userB: %s\n", userB_session_id);
        
        print_validation("User A session validation: ", get_user_id_from_session(userA_session_id));
        print_validation("User B session validation: ", get_user_id_from_session(userB_session_id));
        
        terminate_session(userA_session_id);
        printf("Terminated session for userA.\n");
        
        print_validation("User A session validation after termination: ", get_user_id_from_session(userA_session_id));
        print_validation("User B session validation (should still be valid): ", get_user_id_from_session(userB_session_id));
    }

    return 0;
}