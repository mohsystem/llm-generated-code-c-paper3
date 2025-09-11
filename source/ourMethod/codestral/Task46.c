#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

typedef struct User {
    char* name;
    char* email;
    char* password;
} User;

typedef struct Node {
    User* user;
    struct Node* next;
} Node;

typedef struct HashMap {
    Node** items;
    int size;
} HashMap;

HashMap* createHashMap(int size) {
    HashMap* map = malloc(sizeof(HashMap));
    map->size = size;
    map->items = calloc(size, sizeof(Node*));
    return map;
}

void freeHashMap(HashMap* map) {
    for (int i = 0; i < map->size; i++) {
        Node* node = map->items[i];
        while (node != NULL) {
            Node* temp = node;
            node = node->next;
            free(temp->user->name);
            free(temp->user->email);
            free(temp->user->password);
            free(temp->user);
            free(temp);
        }
    }
    free(map->items);
    free(map);
}

unsigned int hash(const char* str, int size) {
    unsigned int hash = 0;
    for (int i = 0; str[i]; i++) {
        hash = hash * 31 + str[i];
    }
    return hash % size;
}

User* getUser(HashMap* map, const char* email) {
    unsigned int index = hash(email, map->size);
    Node* node = map->items[index];
    while (node != NULL) {
        if (strcmp(node->user->email, email) == 0) {
            return node->user;
        }
        node = node->next;
    }
    return NULL;
}

void insertUser(HashMap* map, User* user) {
    unsigned int index = hash(user->email, map->size);
    Node* node = map->items[index];
    Node* newNode = malloc(sizeof(Node));
    newNode->user = user;
    newNode->next = NULL;
    if (node == NULL) {
        map->items[index] = newNode;
    } else {
        while (node->next != NULL) {
            node = node->next;
        }
        node->next = newNode;
    }
}

char* getHashedPassword(const char* password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    char* hexHash = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hexHash + (i * 2), "%02x", hash[i]);
    }
    hexHash[SHA256_DIGEST_LENGTH * 2] = '\0';
    return hexHash;
}

void registerUser(HashMap* map, const char* name, const char* email, const char* password) {
    if (getUser(map, email) != NULL) {
        fprintf(stderr, "Email already exists\n");
        return;
    }
    char* hashedPassword = getHashedPassword(password);
    User* user = malloc(sizeof(User));
    user->name = strdup(name);
    user->email = strdup(email);
    user->password = hashedPassword;
    insertUser(map, user);
}

int main() {
    HashMap* users = createHashMap(10);
    registerUser(users, "John Doe", "john.doe@example.com", "password123");
    registerUser(users, "Jane Smith", "jane.smith@example.com", "securepassword");
    freeHashMap(users);
    return 0;
}