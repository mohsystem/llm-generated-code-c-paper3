// Note: MongoDB C driver does not support CRUD operations as straightforwardly as other languages.
// Here is a simplified example using the MongoDB C driver.

#include <mongoc/mongoc.h>
#include <stdio.h>

void create(mongoc_collection_t *collection, const char *name, int age, const char *position) {
    bson_t *doc;
    doc = bson_new();
    BSON_APPEND_UTF8(doc, "name", name);
    BSON_APPEND_INT32(doc, "age", age);
    BSON_APPEND_UTF8(doc, "position", position);
    mongoc_collection_insert_one(collection, doc, NULL, NULL, NULL);
    bson_destroy(doc);
}

bson_t *read(mongoc_collection_t *collection, const char *name) {
    bson_t *filter;
    filter = bson_new();
    BSON_APPEND_UTF8(filter, "name", name);
    bson_t *doc;
    doc = bson_new();
    if (mongoc_collection_find_one(collection, filter, NULL, doc, NULL)) {
        bson_destroy(filter);
        return doc;
    }
    bson_destroy(filter);
    bson_destroy(doc);
    return NULL;
}

void update(mongoc_collection_t *collection, const char *name, int age) {
    bson_t *filter;
    filter = bson_new();
    BSON_APPEND_UTF8(filter, "name", name);
    bson_t *update;
    update = bson_new();
    bson_t *set;
    set = bson_new();
    BSON_APPEND_INT32(set, "age", age);
    BSON_APPEND_DOCUMENT(update, "$set", set);
    mongoc_collection_update_one(collection, filter, update, NULL, NULL, NULL);
    bson_destroy(filter);
    bson_destroy(update);
    bson_destroy(set);
}

void delete_(mongoc_collection_t *collection, const char *name) {
    bson_t *filter;
    filter = bson_new();
    BSON_APPEND_UTF8(filter, "name", name);
    mongoc_collection_delete_one(collection, filter, NULL, NULL, NULL);
    bson_destroy(filter);
}

int main() {
    mongoc_init();
    mongoc_client_t *client;
    client = mongoc_client_new("mongodb://localhost:27017");
    mongoc_database_t *database;
    database = mongoc_client_get_database(client, "mydb");
    mongoc_collection_t *collection;
    collection = mongoc_database_get_collection(database, "employees");

    create(collection, "John Doe", 30, "Software Engineer");
    bson_t *readDoc = read(collection, "John Doe");
    if (readDoc) {
        char *json = bson_as_json(readDoc, NULL);
        printf("Read Document: %s\n", json);
        bson_free(json);
        bson_destroy(readDoc);
    }
    update(collection, "John Doe", 31);
    readDoc = read(collection, "John Doe");
    if (readDoc) {
        char *json = bson_as_json(readDoc, NULL);
        printf("Updated Document: %s\n", json);
        bson_free(json);
        bson_destroy(readDoc);
    }
    delete_(collection, "John Doe");
    printf("Document deleted successfully.\n");

    mongoc_collection_destroy(collection);
    mongoc_database_destroy(database);
    mongoc_client_destroy(client);
    mongoc_cleanup();

    return 0;
}