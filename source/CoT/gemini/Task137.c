#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

char* getProductDetails(const char* productName) {
    char* productDetails = NULL; 
    sqlite3* db;
    int rc = sqlite3_open("products.db", &db); // Replace with your database file

    if (rc) {
        char* errmsg = sqlite3_mprintf("Can't open database: %s", sqlite3_errmsg(db));
        return errmsg;  // Return allocated string
    }


    char* sql = sqlite3_mprintf("SELECT * FROM products WHERE product_name = '%q'", productName); // Using '%q' for safe string insertion

    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_free(sql); // Free allocated SQL string


    if (rc != SQLITE_OK) {
        char* errmsg = sqlite3_mprintf("SQL error: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return errmsg;
    }


    rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW) {
        productDetails = sqlite3_mprintf(
           "Product ID: %s\nProduct Name: %s\nPrice: %s\nDescription: %s",
           sqlite3_column_text(stmt, 0), sqlite3_column_text(stmt, 1),
           sqlite3_column_text(stmt, 2), sqlite3_column_text(stmt, 3));

    } else {
       productDetails = sqlite3_mprintf("Product not found.");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return productDetails;
}

int main() {
    char productName[256];
    printf("Enter product name: ");
    scanf("%s", productName);  // Note: vulnerable to buffer overflow if input exceeds 255 characters

    char* details = getProductDetails(productName);
    printf("%s\n", details);
    sqlite3_free(details); // Free allocated memory

    // Test Cases (remember to free the returned strings)
    char* test1 = getProductDetails("Laptop"); printf("%s\n", test1); sqlite3_free(test1);
    char* test2 = getProductDetails("Keyboard"); printf("%s\n", test2); sqlite3_free(test2);
    char* test3 = getProductDetails("Mouse"); printf("%s\n", test3); sqlite3_free(test3);
    char* test4 = getProductDetails("Monitor"); printf("%s\n", test4); sqlite3_free(test4);
    char* test5 = getProductDetails("NonExistentProduct"); printf("%s\n", test5); sqlite3_free(test5);

    return 0;
}