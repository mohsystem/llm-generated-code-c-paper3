#include <stdio.h>
#include <sqlite3.h>

void getProductDetails(const char* productId) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    
    if (sqlite3_open("your_database.db", &db) == SQLITE_OK) {
        const char* sql = "SELECT * FROM products WHERE product_id = ?";
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, productId, -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                printf("Product ID: %s, Name: %s, Price: %s\n",
                       sqlite3_column_text(stmt, 0),
                       sqlite3_column_text(stmt, 1),
                       sqlite3_column_text(stmt, 2));
                // Add more fields as necessary
            }
        }
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);
}

int main() {
    const char* testProductIds[] = {"1", "2", "3", "4", "5"};
    for (int i = 0; i < 5; i++) {
        getProductDetails(testProductIds[i]);
    }

    return 0;
}