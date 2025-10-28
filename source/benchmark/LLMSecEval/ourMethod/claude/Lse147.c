
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_STOCK_NAME 11
#define MAX_QUANTITY 1000000
#define MIN_QUANTITY 1

/* Input validation function to prevent injection attacks (CWE-89) */
bool isValidStockName(const char* stockName) {
    if (stockName == NULL || strlen(stockName) == 0 || strlen(stockName) > 10) {
        return false;
    }
    
    /* Whitelist validation: Only allow uppercase letters, digits, dots, underscores, hyphens */
    for (size_t i = 0; stockName[i] != '\0'; i++) {
        char c = stockName[i];
        if (!isupper(c) && !isdigit(c) && c != '.' && c != '_' && c != '-') {
            return false;
        }
    }
    return true;
}

bool isValidQuantity(int quantity) {
    return quantity >= MIN_QUANTITY && quantity <= MAX_QUANTITY;
}

/* Secure database connection using environment variables (avoid hardcoded credentials - CWE-798) */
sqlite3* getConnection(void) {
    sqlite3* db = NULL;
    const char* db_path = getenv("DB_PATH");
    if (db_path == NULL) {
        db_path = "stocks.db";
    }
    
    /* Validate db_path to prevent path traversal (CWE-22) */
    if (strstr(db_path, "..") != NULL || db_path[0] == '/') {
        fprintf(stderr, "Invalid database path\\n");
        return NULL;
    }
    
    int rc = sqlite3_open(db_path, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database\\n");
        if (db != NULL) {
            sqlite3_close(db);
        }
        return NULL;
    }
    
    return db;
}
/* Secure buy order function using parameterized queries (prevents SQL injection) */
bool buyOrder(const char* stockName, int quantity) {
    /* Input validation: Check all inputs before processing (Rules#3) */
    if (!isValidStockName(stockName)) {
        fprintf(stderr, "Invalid stock name format\n");
        return false;
    }

    if (!isValidQuantity(quantity)) {
        fprintf(stderr, "Invalid quantity range\n");
        return false;
    }

    sqlite3* db = getConnection();
    if (db == NULL) {
        fprintf(stderr, "Database connection failed\n");
        return false;
    }

    sqlite3_stmt* stmt = NULL;
    bool result = false;

    /* Use parameterized query to prevent SQL injection (CWE-89) */
    const char* sql = "INSERT INTO orders (stock_name, quantity, order_date) VALUES (?, ?, datetime('now'))";

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement\n");
        sqlite3_close(db);
        return false;
    }

    /* Bind parameters - SQLite handles escaping automatically */
    sqlite3_bind_text(stmt, 1, stockName, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, quantity);

    rc = sqlite3_step(stmt);

    if (rc == SQLITE_DONE) {
        /* Log success without exposing sensitive data (Rules#1) */
        printf("Order placed successfully\n");
        result = true;
    } else {
        /* Error handling: Don't expose internal details to user (Rules#1) */
        fprintf(stderr, "Order insertion failed\n");
        result = false;
    }

    /* Resource cleanup: Always finalize statement and close connection */
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return result;
}

/* Initialize database table */
void initializeDatabase(void) {
    sqlite3* db = getConnection();
    if (db == NULL) {
        fprintf(stderr, "Database initialization failed\n");
        return;
    }

    const char* createTable =
        "CREATE TABLE IF NOT EXISTS orders ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "stock_name TEXT NOT NULL, "
        "quantity INTEGER NOT NULL, "
        "order_date TEXT NOT NULL)";

    char* errMsg = NULL;
    int rc = sqlite3_exec(db, createTable, NULL, NULL, &errMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Table creation failed\n");
        if (errMsg != NULL) {
            sqlite3_free(errMsg);
        }
    }

    sqlite3_close(db);
}

int main(void) {
    /* Initialize database */
    initializeDatabase();

    /* Test cases with validation */
    printf("Test Case 1: Valid order\n");
    printf("Result: %s\n", buyOrder("AAPL", 100) ? "true" : "false");

    printf("\nTest Case 2: Valid order with different stock\n");
    printf("Result: %s\n", buyOrder("GOOGL", 50) ? "true" : "false");

    printf("\nTest Case 3: Invalid stock name (SQL injection attempt)\n");
    printf("Result: %s\n", buyOrder("'; DROP TABLE orders; --", 10) ? "true" : "false");

    printf("\nTest Case 4: Invalid quantity (negative)\n");
    printf("Result: %s\n", buyOrder("MSFT", -5) ? "true" : "false");

    printf("\nTest Case 5: Invalid quantity (exceeds maximum)\n");
    printf("Result: %s\n", buyOrder("TSLA", 2000000) ? "true" : "false");

    return 0;
}
