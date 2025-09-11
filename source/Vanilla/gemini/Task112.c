#include <stdio.h>
#include <bson/bson.h>
#include <mongoc/mongoc.h>

void perform_crud(const char *name, int age) {
    mongoc_client_t *client;
    mongoc_collection_t *collection;
    bson_error_t error;
    bson_oid_t oid;
    bson_t *document;
    bson_t *query;
    bson_t *update;

    mongoc_init();

    client = mongoc_client_new("mongodb://localhost:27017"); // Replace with your MongoDB connection string
    collection = mongoc_client_get_collection(client, "myDatabase", "myCollection"); // Replace with your database and collection name


    // Create
    document = bson_new();
    bson_oid_init(&oid, NULL);
    bson_append_oid(document, "_id", -1, &oid);
    bson_append_utf8(document, "name", -1, name, -1);
    bson_append_int32(document, "age", -1, age);
    if (!mongoc_collection_insert_one(collection, document, NULL, NULL, &error)) {
        fprintf(stderr, "%s\n", error.message);
    } else {
         printf("Document inserted successfully.\n");
    }
    bson_destroy(document);



    //Read
    query = bson_new();
    bson_append_utf8(query, "name", -1, name, -1);

    mongoc_cursor_t *cursor = mongoc_collection_find_with_opts(collection, query, NULL, NULL);

    const bson_t *doc;
    char *str;
    while (mongoc_cursor_next(cursor, &doc)) {
        str = bson_as_canonical_extended_json(doc, NULL);
        printf("Found Document: %s\n", str);
        bson_free(str);
    }


    if (mongoc_cursor_error(cursor, &error)) {
        fprintf(stderr, "Cursor error: %s\n", error.message);
    }
    mongoc_cursor_destroy(cursor);
    bson_destroy(query);


    //Update
    query = bson_new();
    bson_append_utf8(query, "name", -1, name, -1);
    update = BCON_NEW("$set", "{", "age", BCON_INT32(age + 5), "}");

    if (!mongoc_collection_update_one(collection, query, update, NULL, NULL, &error)) {
       fprintf(stderr, "%s\n", error.message);
    } else {
      printf("Document updated successfully.\n");
    }
    bson_destroy(query);
    bson_destroy(update);



    // Delete
    query = bson_new();
    bson_append_utf8(query, "name", -1, name, -1);


     if (!mongoc_collection_delete_one(collection, query, NULL, NULL, &error)) {
       fprintf(stderr, "%s\n", error.message);

    } else {
         printf("Document deleted successfully.\n");
    }

    bson_destroy(query);


    mongoc_collection_destroy(collection);
    mongoc_client_destroy(client);
    mongoc_cleanup();

}

int main() {

     // Test cases
    perform_crud("Test1", 20);
    perform_crud("Test2", 25);
    perform_crud("Test3", 30);
    perform_crud("Test4", 35);
    perform_crud("Test5", 40);
    return 0;

}