// MongoDB interaction in C requires the MongoDB C driver and a running MongoDB instance. 
// Due to security constraints, direct MongoDB interaction is not implemented here.
// Below is a template code for MongoDB CRUD operations in C:

#include <mongoc/mongoc.h>
#include <bson/bson.h>
#include <stdio.h>

void create_document(mongoc_collection_t *collection, bson_t *document) {
    bson_error_t error;
    if (!mongoc_collection_insert_one(collection, document, NULL, NULL, &error)) {
        fprintf(stderr, "Insert failed: %s\n", error.message);
    }
}

bson_t *read_document(mongoc_collection_t *collection, const char *key, const char *value) {
    bson_t *query = BCON_NEW(key, BCON_UTF8(value));
    mongoc_cursor_t *cursor = mongoc_collection_find_with_opts(collection, query, NULL, NULL);
    const bson_t *doc;
    if (mongoc_cursor_next(cursor, &doc)) {
        bson_t *result = bson_copy(doc);
        bson_destroy(query);
        mongoc_cursor_destroy(cursor);
        return result;
    }
    bson_destroy(query);
    mongoc_cursor_destroy(cursor);
    return NULL;
}

void update_document(mongoc_collection_t *collection, const char *key, const char *value, bson_t *updated_document) {
    bson_t *query = BCON_NEW(key, BCON_UTF8(value));
    bson_t *update = BCON_NEW("$set", BCON_DOCUMENT(updated_document));
    bson_error_t error;
    if (!mongoc_collection_update_one(collection, query, update, NULL, NULL, &error)) {
        fprintf(stderr, "Update failed: %s\n", error.message);
    }
    bson_destroy(query);
    bson_destroy(update);
}

void delete_document(mongoc_collection_t *collection, const char *key, const char *value) {
    bson_t *query = BCON_NEW(key, BCON_UTF8(value));
    bson_error_t error;
    if (!mongoc_collection_delete_one(collection, query, NULL, NULL, &error)) {
        fprintf(stderr, "Delete failed: %s\n", error.message);
    }
    bson_destroy(query);
}

int main() {
    mongoc_init();
    mongoc_client_t *client = mongoc_client_new("mongodb://localhost:27017");
    mongoc_collection_t *collection = mongoc_client_get_collection(client, "myDatabase", "myCollection");

    bson_t *doc1 = BCON_NEW("name", BCON_UTF8("John Doe"), "age", BCON_INT32(29));
    bson_t *doc2 = BCON_NEW("name", BCON_UTF8("Jane Doe"), "age", BCON_INT32(25));
    bson_t *doc3 = BCON_NEW("name", BCON_UTF8("Alice"), "age", BCON_INT32(32));
    bson_t *doc4 = BCON_NEW("name", BCON_UTF8("Bob"), "age", BCON_INT32(45));
    bson_t *doc5 = BCON_NEW("name", BCON_UTF8("Charlie"), "age", BCON_INT32(35));

    // Create
    create_document(collection, doc1);
    create_document(collection, doc2);
    create_document(collection, doc3);
    create_document(collection, doc4);
    create_document(collection, doc5);

    // Read
    bson_t *doc = read_document(collection, "name", "John Doe");
    if (doc) {
        char *str = bson_as_json(doc, NULL);
        printf("Read: %s\n", str);
        bson_free(str);
        bson_destroy(doc);
    }

    // Update
    bson_t *updatedDoc = BCON_NEW("age", BCON_INT32(30));
    update_document(collection, "name", "John Doe", updatedDoc);
    bson_destroy(updatedDoc);

    // Delete
    delete_document(collection, "name", "Jane Doe");

    // Cleanup
    bson_destroy(doc1);
    bson_destroy(doc2);
    bson_destroy(doc3);
    bson_destroy(doc4);
    bson_destroy(doc5);
    mongoc_collection_destroy(collection);
    mongoc_client_destroy(client);
    mongoc_cleanup();

    return 0;
}