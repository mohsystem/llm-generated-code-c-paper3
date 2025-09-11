#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <regex.h> // For input validation in C
#include <bcrypt.h>


const char* DB_FILE = "users.db";  // Securely store DB credentials


//Basic input validation using regex.h 
int is_valid_input(const char* name, const char *email, const char *password) {

	if (name == NULL || email == NULL || password == NULL || strlen(name) == 0 || strlen(email) == 0 || strlen(password) == 0){
		return 0;
	}
	
    regex_t regex_email;
    int reti_email;

    reti_email = regcomp(&regex_email, "^[A-Za-z0-9+_.-]+@(.+)$", REG_EXTENDED);
    if (reti_email) {
        fprintf(stderr, "Could not compile regex\n");
        return 0; // Or handle the error appropriately
    }

    reti_email = regexec(&regex_email, email, 0, NULL, 0);
    if (reti_email == REG_NOMATCH) {
        return 0; // Email does not match
    }

    regfree(&regex_email);


    regex_t regex_password;
    int reti_password;

    reti_password = regcomp(&regex_password, "^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).{8,}$", REG_EXTENDED);
    if (reti_password) {
        fprintf(stderr, "Could not compile regex\n");
        return 0; // Or handle the error appropriately
    }

    reti_password = regexec(&regex_password, password, 0, NULL, 0);
    if (reti_password == REG_NOMATCH) {
        return 0; // Password does not match
    }

    regfree(&regex_password);

    return 1; // Valid input

}




char* hash_password(const char* password) {
    char salt[BCRYPT_HASHSIZE];
    char* hash = malloc(BCRYPT_HASHSIZE * sizeof(char)); // Allocate memory for hash

    bcrypt_gensalt(12, salt);       // Generate a salt with work factor 12
    bcrypt_hashpw(password, salt, hash);

    return hash;
}


int register_user(const char* name, const char* email, const char* password) {
    // Problem understanding: Collect user data, validate, hash password, store in DB.
    // Security requirements: Prevent SQL injection, hash passwords.

    // Input validation (CWE-20, CWE-23, CWE-79, CWE-89, etc.)
    if (!is_valid_input(name, email, password)) {
        fprintf(stderr, "Invalid input. Registration failed.\n");
        return 1; 
    }

    char* hashed_password = hash_password(password); // Hash password (CWE-256, CWE-257, CWE-327, CWE-759, CWE-916)


    sqlite3* db;
    char* err_msg = 0;

    int rc = sqlite3_open(DB_FILE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db)); // Avoid CWE-209
        sqlite3_close(db);
        free(hashed_password);  // Free allocated memory
        return 1;
    }

    char* sql = sqlite3_mprintf("INSERT INTO users(name, email, password) VALUES('%q', '%q', '%q')", name, email, hashed_password);  // Parameterized query (CWE-89)

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);  // Avoid CWE-209
        sqlite3_free(err_msg);
        sqlite3_close(db);
        free(hashed_password);  // Free allocated memory
        return 1;
    }

    sqlite3_close(db);
    printf("User registered successfully.\n");
    free(hashed_password); // Free the allocated memory for the hash
    sqlite3_free(sql); // Free the memory allocated by sqlite3_mprintf
    return 0;
}


int main() {
    // Test cases
    register_user("John Doe", "john.doe@example.com", "SecureP@sswOrd1");
    register_user("Jane Smith", "jane.smith@example.com", "P@$$wOrd2");
    register_user("", "invalid.email", "weak"); // Invalid input
    register_user("User3", "user3@example.com", "AnotherSecureP@sswOrd3");
    register_user("User4", NULL, "P@$$wOrd4"); // Invalid input  

    return 0;
}