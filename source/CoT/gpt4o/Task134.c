#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rand.h>

typedef struct {
    char keyId[10];
    unsigned char key[32]; // AES-256
} KeyEntry;

typedef struct {
    KeyEntry *entries;
    size_t size;
    size_t capacity;
} Task134;

void init(Task134 *manager) {
    manager->entries = malloc(sizeof(KeyEntry) * 10);
    manager->size = 0;
    manager->capacity = 10;
}

void freeManager(Task134 *manager) {
    free(manager->entries);
}

char* createKey(Task134 *manager, const char *algorithm) {
    if (strcmp(algorithm, "AES") != 0) {
        fprintf(stderr, "Unsupported algorithm\n");
        exit(1);
    }

    if (manager->size >= manager->capacity) {
        manager->capacity *= 2;
        manager->entries = realloc(manager->entries, sizeof(KeyEntry) * manager->capacity);
    }

    if (!RAND_bytes(manager->entries[manager->size].key, sizeof(manager->entries[manager->size].key))) {
        fprintf(stderr, "Key generation failed\n");
        exit(1);
    }

    sprintf(manager->entries[manager->size].keyId, "key%zu", manager->size);
    manager->size++;
    return manager->entries[manager->size - 1].keyId;
}

unsigned char* getKey(Task134 *manager, const char *keyId) {
    for (size_t i = 0; i < manager->size; i++) {
        if (strcmp(manager->entries[i].keyId, keyId) == 0) {
            return manager->entries[i].key;
        }
    }
    return NULL;
}

void deleteKey(Task134 *manager, const char *keyId) {
    for (size_t i = 0; i < manager->size; i++) {
        if (strcmp(manager->entries[i].keyId, keyId) == 0) {
            for (size_t j = i; j < manager->size - 1; j++) {
                manager->entries[j] = manager->entries[j + 1];
            }
            manager->size--;
            return;
        }
    }
}

int main() {
    Task134 manager;
    init(&manager);

    char *keyId1 = createKey(&manager, "AES");
    char *keyId2 = createKey(&manager, "AES");
    char *keyId3 = createKey(&manager, "AES");
    char *keyId4 = createKey(&manager, "AES");
    char *keyId5 = createKey(&manager, "AES");

    printf("KeyId1: %s Key: %s\n", keyId1, getKey(&manager, keyId1));
    printf("KeyId2: %s Key: %s\n", keyId2, getKey(&manager, keyId2));
    printf("KeyId3: %s Key: %s\n", keyId3, getKey(&manager, keyId3));
    printf("KeyId4: %s Key: %s\n", keyId4, getKey(&manager, keyId4));
    printf("KeyId5: %s Key: %s\n", keyId5, getKey(&manager, keyId5));

    deleteKey(&manager, keyId3);
    printf("After deletion, KeyId3: %s\n", getKey(&manager, keyId3));

    freeManager(&manager);
    return 0;
}