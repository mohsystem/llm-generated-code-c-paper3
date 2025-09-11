
// MongoDB operations in pure C require MongoDB C driver
// This is a basic example using the MongoDB C driver

#include <stdio.h>
#include <stdlib.h>
#include <mongoc/mongoc.h>
#include <bson/bson.h>

typedef struct {
    mongoc_client_t *client;
    mongoc_database_t *database;
    mongoc_collection_t *collection;
} Task112;

Task112* init_db() {
    Task112 *db = malloc(sizeof(Task112));
    if (!db) return NULL;

    const char *uri_string = getenv("MONGODB_URI");
    if (!uri_string) {
        fprintf(stderr, "MONGODB_URI environment variable not set\\n");
        free(db);
        return NULL;
    }

    mongoc_init();

    bson_error_t error;
    mongoc_uri_t *uri = mongoc_uri_new_with_error(uri_string, &error);
    if (!uri) {
        fprintf(stderr, "Failed to parse URI: %s\\n", error.message);
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

int create_document(Task112 *db, const char *name, int age) {
    bson_error_t error;
    bson_t *doc = bson_new();
    BSON_APPEND_UTF8(doc, "name", name);
    BSON_APPEND_INT32(doc, "age", age);

    if (!mongoc_collection_insert_one(db->collection, doc, NULL, NULL, &error)) {
        fprintf(stderr, "Insert failed: %s\\n", error.message);
        bson_destroy(doc);
        return 0;
    }

    bson_destroy(doc);
    return 1;
}

bson_t* read_document(Task112 *db, const char *name) {
    bson_error_t error;
    bson_t *query = bson_new();
    BSON_APPEND_UTF8(query, "name", name);

    mongoc_cursor_t *cursor = mongoc_collection_find_with_opts(
        db->collection, query, NULL, NULL);

    const bson_t *doc;
    bson_t *result = NULL;
    if (mongoc_cursor_next(cursor, &doc)) {
        result = bson_copy(doc);
    }

    mongoc_cursor_destroy(cursor);
    bson_destroy(query);
    return result;
}

int update_document(Task112 *db, const char *name, int new_age) {
    bson_error_t error;
    bson_t *query = bson_new();
    bson_t *update = bson_new();
    bson_t *set = bson_new();

    BSON_APPEND_UTF8(query, "name", name);
    BSON_APPEND_INT32(set, "age", new_age);
    BSON_APPEND_DOCUMENT(update, "$set", set);

    if (!mongoc_collection_update_one(db->collection, query, update, 
                                    NULL, NULL, &error)) {
        fprintf(stderr, "Update failed: %s\\n", error.message);
        bson_destroy(query);
        bson_destroy(update);
        bson_destroy(set);
        return 0;
    }

    bson_destroy(query);
    bson_destroy(update);
    bson_destroy(set);
    return 1;
}

int delete_document(Task112 *db, const char *name) {
    bson_error_t error;
    bson_t *query = bson_new();
    BSON_APPEND_UTF8(query, "name", name);

    if (!mongoc_collection_delete_one(db->collection, query, NULL, NULL, &error)) {
        fprintf(stderr, "Delete failed: %s\\n", error.message);
        bson_destroy(query);
        return 0;
    }

    bson_destroy(query);
    return 1;
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
    if (!db) {
        fprintf(stderr, "Failed to initialize database\\n");
        return 1;
    }

    // Test Case 1: Create
    if (create_document(db, "John Doe", 25)) {
        printf("Created document for John Doe\\n");
    }

    // Test Case 2: Read
    bson_t *doc = read_document(db, "John Doe");
    if (doc) {
        char *str = bson_as_json(doc, NULL);
        ', type='text')