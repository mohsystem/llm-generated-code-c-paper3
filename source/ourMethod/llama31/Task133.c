#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sqlite3.h>
#include <openssl/sha.h>

void resetPassword(const char* userEmail, const char* newPassword) {
    // Generate a secure token
    char token[65];
    for (int i = 0; i < 64; ++i) {
        token[i] = 'a' + (rand() % 26);
    }
    token[64] = '\0';

    // Store the token in the database
    storeTokenInDatabase(userEmail, token);

    // Send the token to the user via email
    sendTokenViaEmail(userEmail, token);

    // Verify the token and update the password
    verifyTokenAndResetPassword(userEmail, token, newPassword);
}

void storeTokenInDatabase(const char* userEmail, const char* token) {
    sqlite3* db;
    char* errorMessage;
    int rc = sqlite3_open("password_reset.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }
    const char* query = "INSERT INTO password_reset_tokens (user_id, token, token_expiry) VALUES (?, ?, ?)";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return;
    }
    sqlite3_bind_text(stmt, 1, userEmail, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, token, -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 3, time(0) + 15 * 60);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void sendTokenViaEmail(const char* userEmail, const char* token) {
    // Simulate sending an email
    printf("Sending token to %s: %s\n", userEmail, token);
}

void verifyTokenAndResetPassword(const char* userEmail, const char* token, const char* newPassword) {
    sqlite3* db;
    char* errorMessage;
    int rc = sqlite3_open("password_reset.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }
    const char* query = "SELECT * FROM password_reset_tokens WHERE user_id = ? AND token = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return;
    }
    sqlite3_bind_text(stmt, 1, userEmail, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, token, -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        int64_t expiry = sqlite3_column_int64(stmt, 2);
        if (expiry > time(0)) {
            // Update the password
            query = "UPDATE users SET password = ? WHERE email = ?";
            rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
            if (rc != SQLITE_OK) {
                fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
                return;
            }
            char hashedPassword[SHA256_DIGEST_LENGTH * 2 + 1];
            hashPassword(newPassword, hashedPassword);
            sqlite3_bind_text(stmt, 1, hashedPassword, -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, userEmail, -1, SQLITE_STATIC);
            rc = sqlite3_step(stmt);
            if (rc != SQLITE_DONE) {
                fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
                return;
            }
            sqlite3_finalize(stmt);
            printf("Password reset successfully.\n");
        } else {
            printf("Invalid or expired token.\n");
        }
    } else {
        printf("Invalid or expired token.\n");
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void hashPassword(const char* password, char* hashedPassword) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashedPassword + i * 2, "%02x", hash[i]);
    }
    hashedPassword[SHA256_DIGEST_LENGTH * 2] = '\0';
}

int main() {
    srand(time(0));
    // Test cases
    resetPassword("user@example.com", "NewPassword123!");
    return 0;
}