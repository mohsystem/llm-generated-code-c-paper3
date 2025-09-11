#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <uuid/uuid.h>

// Structure to represent a session
typedef struct {
    char username[50];
    time_t creation_time;
} Session;

// Structure for a session entry in the hash table
typedef struct {
    uuid_t session_id;
    Session session;
} SessionEntry;


// Simple hash table implementation (replace with a more robust one if needed)
#define TABLE_SIZE 100

SessionEntry* hash_table[TABLE_SIZE];

int hash_function(uuid_t session_id) {
    unsigned char *p = session_id;
    unsigned int h = 0;
    for (int i = 0; i < sizeof(uuid_t); i++) {
        h = 31 * h + *p++;
    }
    return h % TABLE_SIZE;
}


char* create_session(const char* username) {
    uuid_t session_id;
    uuid_generate(session_id);


    int index = hash_function(session_id);
    
    SessionEntry *new_entry = (SessionEntry *)malloc(sizeof(SessionEntry));
    if (new_entry == NULL) {
        perror("Failed to allocate memory for session");
        return NULL; 
    }

    memcpy(new_entry->session_id, session_id, sizeof(uuid_t));
    strncpy(new_entry->session.username, username, sizeof(new_entry->session.username) - 1);
    new_entry->session.creation_time = time(NULL);


    hash_table[index] = new_entry;
    

    char* session_id_str = (char*)malloc(37 * sizeof(char)); // Memory for string representation
    if (session_id_str == NULL) {
        perror("Memory allocation failed");
        free(new_entry); // Free the allocated entry
        return NULL;
    }
    uuid_unparse(session_id, session_id_str);
    return session_id_str;
}

Session* get_session(const char* session_id_str) {
    uuid_t session_id;
    if (uuid_parse(session_id_str, session_id) != 0) {
        return NULL;
    }
    int index = hash_function(session_id);
    if (hash_table[index] != NULL && uuid_compare(hash_table[index]->session_id, session_id) == 0) {
        return &hash_table[index]->session;
    }
    return NULL;
}

void invalidate_session(const char* session_id_str) {
    uuid_t session_id;
    if (uuid_parse(session_id_str, session_id) != 0) {
        return;
    }
    int index = hash_function(session_id);
    if (hash_table[index] != NULL && uuid_compare(hash_table[index]->session_id, session_id) == 0) {
        free(hash_table[index]);
        hash_table[index] = NULL;
    }
}

int main() {
    // Test Cases
    char* session_id1 = create_session("user1");
    Session* s1 = get_session(session_id1);
    if (s1) printf("Session 1: %s %ld\n", s1->username, s1->creation_time);


    char* session_id2 = create_session("user2");
    Session* s2 = get_session(session_id2);
    if (s2) printf("Session 2: %s %ld\n", s2->username, s2->creation_time);


    invalidate_session(session_id1);
    Session *invalid_session = get_session(session_id1);
    if(invalid_session) printf("Invalidated session: %s\n", invalid_session->username);
    else printf("Invalidated Session: NULL\n");

    char* session_id3 = create_session("user3");
    Session* s3 = get_session(session_id3);
    if (s3) printf("Session 3: %s %ld\n", s3->username, s3->creation_time);

    char* session_id4 = create_session("user4");
    Session* s4 = get_session(session_id4);
    if (s4) printf("Session 4: %s %ld\n", s4->username, s4->creation_time);

    char* session_id5 = create_session("user5");
    Session* s5 = get_session(session_id5);
    if (s5) printf("Session 5: %s %ld\n", s5->username, s5->creation_time);

    free(session_id1); 
    free(session_id2);
    free(session_id3);
    free(session_id4);
    free(session_id5);

    return 0;
}