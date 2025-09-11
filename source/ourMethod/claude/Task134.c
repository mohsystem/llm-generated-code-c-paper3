
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_KEYS 100
#define KEY_SIZE 32
#define ID_SIZE 16

typedef struct {
    unsigned char key[KEY_SIZE];
    char id[ID_SIZE + 1];
    time_t creation_time;
    time_t expiration_time;
    bool is_valid;
} KeyEntry;

typedef struct {
    KeyEntry keys[MAX_KEYS];
    int count;
} KeyStore;

void generate_random_bytes(unsigned char* buffer, size_t size) {
    for(size_t i = 0; i < size; i++) {
        buffer[i] = (unsigned char)(rand() % 256);
    }
}

void generate_random_id(char* id_buffer) {
    const char charset[] = "0123456789ABCDEF";
    for(int i = 0; i < ID_SIZE; i++) {
        id_buffer[i] = charset[rand() % 16];
    }
    id_buffer[ID_SIZE] = '\\0';
}

bool generate_key(KeyStore* store, int validity_hours, char* out_id) {
    if(store->count >= MAX_KEYS) {
        return false;
    }
    
    KeyEntry* entry = &store->keys[store->count];
    
    // Generate random key
    generate_random_bytes(entry->key, KEY_SIZE);
    
    // Generate random ID
    generate_random_id(entry->id);
    strcpy(out_id, entry->id);
    
    // Set times
    entry->creation_time = time(NULL);
    entry->expiration_time = entry->creation_time + (validity_hours * 3600);
    entry->is_valid = true;
    
    store->count++;
    return true;
}

KeyEntry* find_key(KeyStore* store, const char* key_id) {
    for(int i = 0; i < store->count; i++) {
        if(strcmp(store->keys[i].id, key_id) == 0 && store->keys[i].is_valid) {
            return &store->keys[i];
        }
    }
    return NULL;
}

bool get_key(KeyStore* store, const char* key_id, unsigned char* out_key) {
    KeyEntry* entry = find_key(store, key_id);
    if(!entry) {
        return false;
    }
    
    time_t now = time(NULL);
    if(now > entry->expiration_time) {
        entry->is_valid = false;
        return false;
    }
    
    memcpy(out_key, entry->key, KEY_SIZE);
    return true;
}

void revoke_key(KeyStore* store, const char* key_id) {
    KeyEntry* entry = find_key(store, key_id);
    if(entry) {
        entry->is_valid = false;
    }
}

bool is_key_valid(KeyStore* store, const char* key_id) {
    KeyEntry* entry = find_key', type='text')