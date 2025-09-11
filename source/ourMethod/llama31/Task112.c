#include <bson/bson.h>
#include <mongoc/mongoc.h>
#include <stdio.h>

int main() {
    mongoc_init();

    // Connect to MongoDB
    mongoc_client_t *client = mongoc_client_new("mongodb://localhost:27017");
    mongoc_collection_t *collection = mongoc_client_get_collection(client, "mydb", "employees");

    // Create
    bson_t *doc = BCON_NEW("name", BCON_UTF8("John Doe"), "age", BCON_INT32(30), "position", BCON_UTF8("Software Engineer"));
    if (mongoc_collection_insert_one(collection, doc, NULL, NULL, NULL)) {
        printf("Document inserted successfully.\n");
    }
    bson_destroy(doc);

    // Read
    bson_t *query = BCON_NEW("name", BCON_UTF8("John Doe"));
    mongoc_cursor_t *cursor = mongoc_collection_find_with_opts(collection, query, NULL, NULL);
    const bson_t *found_doc;
    if (mongoc_cursor_next(cursor, &found_doc)) {
        char *json = bson_as_json(found_doc, NULL);
        printf("Found document: %s\n", json);
        bson_free(json);
    } else {
        printf("No document found with the specified criteria.\n");
    }
    bson_destroy(query);
    mongoc_cursor_destroy(cursor);

    // Update
    bson_t *update = BCON_NEW("$set", "{", "age", BCON_INT32(31), "}");
    if (mongoc_collection_update_one(collection, query, update, NULL, NULL, NULL)) {
        printf("Document updated successfully.\n");
    }
    bson_destroy(update);

    // Delete
    if (mongoc_collection_delete_one(collection, query, NULL, NULL, NULL)) {
        printf("Document deleted successfully.\n");
    }

    bson_destroy(query);
    mongoc_collection_destroy(collection);
    mongoc_client_destroy(client);
    mongoc_cleanup();

    return 0;
}