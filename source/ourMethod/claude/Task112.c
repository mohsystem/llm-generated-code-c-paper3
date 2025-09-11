
// MongoDB C driver does not provide a simple interface like other languages
// Here's a basic example using the mongoc driver
#include <mongoc/mongoc.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    mongoc_client_t *client;
    mongoc_database_t *database;
    mongoc_collection_t *collection;
} Task112;

Task112* init_db() {
    Task112 *db = malloc(sizeof(Task112));
    if (!db) return NULL;
    
    mongoc_init();
    
    // Use connection string with authentication
    const char *uri_string = "mongodb://username:password@localhost:27017";
    mongoc_uri_t *uri = mongoc_uri_new_with_error(uri_string, NULL);
    if (!uri) {
        fprintf(stderr, "Failed to parse URI\\n");
        free(db);
        return NULL;
    }
    
    db->client = mongoc_client_new_from_uri(uri);
    if (!db->client) {
        fprintf(stderr, "Failed to create client\\n");
        mongoc_uri_destroy(uri);
        free(db);
        return NULL;
    }
    
    db->database = mongoc_client_get_database(db->client, "testdb");
    db->collection = mongoc_client_get_collection(db->client, "testdb", "users");
    
    mongoc_uri_destroy(uri);
    return db;
}

void create_document(Task112 *db, const char *name, int age) {
    bson_error_t error;
    bson_t *doc = bson_new();
    
    BSON_APPEND_UTF8(doc, "name", name);
    BSON_APPEND_INT32(doc, "age", age);
    
    if (!mongoc_collection_insert_one(db->collection, doc, NULL, NULL, &error)) {
        fprintf(stderr, "Error creating document: %s\\n", error.message);
    }
    
    bson_destroy(doc);
}

void read_document(Task112 *db, const char *name) {
    bson_error_t error;
    bson_t *query = bson_new();
    mongoc_cursor_t *cursor;
    const bson_t *doc;
    
    BSON_APPEND_UTF8(query, "name", name);
    
    cursor = mongoc_collection_find_with_opts(db->collection, query, NULL, NULL);
    
    while (mongoc_cursor_next(cursor, &doc)) {
        char *str = bson_as_canonical_extended_json(doc, NULL);
        printf("Read: %s\\n", str);
        bson_free(str);
    }
    
    if (mongoc_cursor_error(cursor, &error)) {
        fprintf(stderr, "Error reading document: %s\\n", error.message);
    }
    
    mongoc_cursor_destroy(cursor);
    bson_destroy(query);
}

void update_document(Task112 *db, const char *name, int new_age) {
    bson_error_t error;
    bson_t *query = bson_new();
    bson_t *update = bson_new();
    bson_t *set = bson_new();
    
    BSON_APPEND_UTF8(query, "name", name);
    BSON_APPEND_INT32(set, "age", new_age);
    BSON_APPEND_DOCUMENT(update, "$set", set);
    
    if (!mongoc_collection_update_one(db->collection, query, update, NULL, NULL, &error)) {
        fprintf(stderr, "Error updating document: %s\\n", error.message);
    }
    
    bson_destroy(query);
    bson_destroy(update);
    bson_destroy(set);
}

void delete_document(Task112 *db, const char *name) {
    bson_error_t error;
    bson_t *query = bson_new();
    
    BSON_APPEND_UTF8(query, "name", name);
    
    if (!mongoc_collection_delete_one(db->collection, query, NULL, NULL, &error)) {
        fprintf(stderr, "Error deleting document: %s\\n", error.message);
    }
    
    bson_destroy(query);
}

void cleanup_db(Task112 *db) {
    if (db) {
        mongoc_collection_destroy(db->collection);
        mongoc_database_destroy(db->database);
        mongoc_client_destroy(db->client);
        mongoc_cleanup();
        free(db);
    }
}

int main() {
    Task112 *db = init_db();
    if (!db) return 1;
    
    // Test case 1: Create
    create_document(db, "John", 25);
    
    // Test case 2: Read
    read_document(db, "John");
    
    // Test case 3: Update
    update_document(db, "John", 26);
    read_document(db, "John");
    
    // Test case 4: Delete
    delete_document(db, "John");
    read_document(db, "John");
    
    // Test case 5: Create multiple
    create_document(db, "Alice", 30);
    create_document(db, "Bob", 35);
    
    cleanup_db(db);
    return 0;
}
