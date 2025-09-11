// C99 or later required
#include <mongoc.h>

int main (int argc, char *argv[]) {
    mongoc_client_t *client;
    mongoc_collection_t *collection;
    bson_error_t error;
    bson_oid_t oid;
    bson_t *doc;
    char *str;
    bool retval;

    mongoc_init ();

    client = mongoc_client_new ("mongodb://localhost:27017/");
    collection = mongoc_client_get_collection (client, "test", "test");

    // Create
    doc = BCON_NEW ("name", BCON_UTF8 ("MongoDB"), "type", BCON_UTF8 ("database"));
    if (!mongoc_collection_insert_one (collection, doc, NULL, NULL, &error)) {
        fprintf (stderr, "%s\n", error.message);
        return 1;
    }
    bson_destroy (doc);

    // Read
    doc = mongoc_collection_find_one (collection, NULL, NULL, NULL);
    if (doc) {
        str = bson_as_json (doc, NULL);
        printf ("%s\n", str);
        bson_free (str);
        bson_destroy (doc);
    }

    // Update
    doc = BCON_NEW ("$set", "{", "type", BCON_UTF8 ("NoSQL database"), "}");
    if (!mongoc_collection_update_one (collection, BCON_NEW ("name", BCON_UTF8 ("MongoDB")), doc, NULL, NULL, &error)) {
        fprintf (stderr, "%s\n", error.message);
        return 1;
    }
    bson_destroy (doc);

    // Delete
    if (!mongoc_collection_delete_one (collection, BCON_NEW ("name", BCON_UTF8 ("MongoDB")), NULL, NULL, &error)) {
        fprintf (stderr, "%s\n", error.message);
        return 1;
    }

    mongoc_collection_destroy (collection);
    mongoc_client_destroy (client);
    mongoc_cleanup ();

    return 0;
}