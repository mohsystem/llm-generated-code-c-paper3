#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OBJECTS 100

typedef struct {
    char* key;
    void* object;
} ObjectEntry;

typedef struct {
    ObjectEntry entries[MAX_OBJECTS];
    int count;
} Task108;

void initServer(Task108* server) {
    server->count = 0;
}

void addObject(Task108* server, const char* key, void* obj) {
    if (server->count < MAX_OBJECTS) {
        server->entries[server->count].key = strdup(key);
        server->entries[server->count].object = obj;
        server->count++;
    }
}

void* getObject(Task108* server, const char* key) {
    for (int i = 0; i < server->count; i++) {
        if (strcmp(server->entries[i].key, key) == 0) {
            return server->entries[i].object;
        }
    }
    return NULL;
}

void removeObject(Task108* server, const char* key) {
    for (int i = 0; i < server->count; i++) {
        if (strcmp(server->entries[i].key, key) == 0) {
            free(server->entries[i].key);
            for (int j = i; j < server->count - 1; j++) {
                server->entries[j] = server->entries[j + 1];
            }
            server->count--;
            break;
        }
    }
}

int main() {
    Task108 server;
    initServer(&server);
    
    char* obj1 = "Object1";
    addObject(&server, "1", obj1);
    printf("%s\n", (char*)getObject(&server, "1"));

    int obj2 = 12345;
    addObject(&server, "2", &obj2);
    printf("%d\n", *(int*)getObject(&server, "2"));

    double obj3 = 67.89;
    addObject(&server, "3", &obj3);
    printf("%f\n", *(double*)getObject(&server, "3"));

    removeObject(&server, "1");
    if (getObject(&server, "1") == NULL) {
        printf("null\n");
    }

    int array[] = {1, 2, 3};
    addObject(&server, "4", array);
    int* arrayPtr = (int*)getObject(&server, "4");
    for (int i = 0; i < 3; i++) {
        printf("%d ", arrayPtr[i]);
    }
    printf("\n");

    return 0;
}