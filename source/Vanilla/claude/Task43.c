
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SESSIONS 100
#define SESSION_ID_LENGTH 32
#define SESSION_TIMEOUT_SECONDS 1800 // 30 minutes

typedef struct {
    char session_id[SESSION_ID_LENGTH + 1];
    char user_id[64];
    time_t last_accessed;
    int is_active;
} Session;

typedef struct {
    Session sessions[MAX_SESSIONS];
    int session_count;
} SessionManager;

void generate_session_id(char* session_id) {
    const char charset[] = "0123456789abcdef";
    for (int i = 0; i < SESSION_ID_LENGTH; i++) {
        int index = rand() % 16;
        session_id[i] = charset[index];
    }
    session_id[SESSION_ID_LENGTH] = '\\0';
}

void init_session_manager(SessionManager* manager) {
    manager->session_count = 0;
    memset(manager->sessions, 0, sizeof(Session) * MAX_SESSIONS);
}

char* create_session(SessionManager* manager, const char* user_id) {
    if (manager->session_count >= MAX_SESSIONS) {
        return NULL;
    }
    
    Session* session = &manager->sessions[manager->session_count++];
    generate_session_id(session->session_id);
    strncpy(session->user_id, user_id, 63);
    session->user_id[63] = '\\0';
    session->last_accessed = time(NULL);
    session->is_active = 1;
    
    return session->session_id;
}

int validate_session(SessionManager* manager, const char* session_id) {
    for (int i = 0; i < manager->session_count; i++) {
        if (strcmp(manager->sessions[i].session_id, session_id) == 0 && 
            manager->sessions[i].is_active) {
            time_t current_time = time(NULL);
            if (current_time - manager->sessions[i].last_accessed <= SESSION_TIMEOUT_SECONDS) {
                manager->sessions[i].last_accessed = current_time;
                return 1;
            } else {
                manager->sessions[i].is_active = 0;
                return 0;
            }
        }
    }
    return 0;
}

void terminate_session(SessionManager* manager, const char* session_id) {
    for (int i = 0; i < manager->session_count; i++) {
        if (strcmp(manager->sessions[i].session_id, session_id) == 0) {
            manager->sessions[i].is_active = 0;
            break;
        }
    }
}

int main() {
    srand(time(NULL));
    SessionManager manager;
    init_session_manager(&manager);
    
    // Test case 1: Create and validate session
    char* session_id1 = create_session(&manager, "user1");
    printf("Test 1 - Session valid: %d\\n", validate_session(&manager, session_id1));
    
    // Test case 2: Terminate session
    terminate_session(&manager, session_id1);
    printf("Test 2 - Session valid after termination: %d\\n", validate_session(&manager, session_id1));
    
    // Test case 3: Multiple sessions
    char* session_id2 = create_session(&manager, "user2");
    char* session_id3 = create_session(&manager, "user3");
    printf("Test 3 - Multiple sessions valid: %d\\n", 
           validate_session(&manager, session_id2) && validate_session(&manager, session_id3));
    
    // Test case 4: Invalid session
    printf("Test 4 - Invalid session check: %d\\n", validate_session(&manager, "invalid-session-id"));
    
    // Test case 5: Session timeout simulation
    char* session_id4 = create_session(&manager, "user4");
    printf("Test 5 - New session valid: %d\\n", validate_session(&manager, session_id4));
    
    return 0;
}
