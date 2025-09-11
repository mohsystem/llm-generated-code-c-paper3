// C code
// Note: This requires the MongoDB C Driver
#include <mongoc.h>

void createDocument(mongoc_collection_t *collection, const char *id, const char *data) {
    bson_t *document = BCON_NEW("_id", BCON_UTF8(id), "data", BCON_UTF8(data));
    bson_error_t error;
    mongoc_collection_insert_one(collection, document, NULL, NULL, &error);
    bson_destroy(document);
}

void readDocument(mongoc_collection_t *collection, const char *id) {
    bson_t *filter = BCON_NEW("_id", BCON_UTF8(id));
    bson_t reply;
    bson_error_t error;
    mongoc_cursor_t *cursor = mongoc_collection_find_with_opts(collection, filter, NULL, NULL);
    if (mongoc_cursor_next(cursor, &reply)) {
        char *str = bson_as_json(&reply, NULL);
        printf("%s\n", str);
        bson_free(str);
    } else {
        printf("Document not found.\n");
    }
    mongoc_cursor_destroy(cursor);
    bson_destroy(filter);
}

void updateDocument(mongoc_collection_t *collection, const char *id, const char *data) {
    bson_t *filter = BCON_NEW("_id", BCON_UTF8(id));
    bson_t *update = BCON_NEW("$set", "{", "data", BCON_UTF8(data), "}");
    bson_error_t error;
    mongoc_collection_update_one(collection, filter, update, NULL, NULL, &error);
    bson_destroy(filter);
    bson_destroy(update);
}

void deleteDocument(mongoc_collection_t *collection, const char *id) {
    bson_t *filter = BCON_NEW("_id", BCON_UTF8(id));
    bson_error_t error;
    mongoc_collection_delete_one(collection, filter, NULL, NULL, &error);
    bson_destroy(filter);
}

int main() {
    mongoc_init();
    mongoc_client_t *client = mongoc_client_new("mongodb://localhost:27017");
    mongoc_database_t *database = mongoc_client_get_database(client, "test");
    mongoc_collection_t *collection = mongoc_database_get_collection(database, "testCollection");

    // Test cases
    createDocument(collection, "testId1", "testData1");
    readDocument(collection, "testId1");
    updateDocument(collection, "testId1", "updatedData1");
    readDocument(collection, "testId1");
    deleteDocument(collection, "testId1");

    mongoc_collection_destroy(collection);
    mongoc_database_destroy(database);
    mongoc_client_destroy(client);
    mongoc_cleanup();

    return 0;
}