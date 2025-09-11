#include <bcrypt.h>
// assuming a hypothetical database connection
#include "database_connection.h"

void updatePassword(char* username, char* newPassword) {
    char hashedPassword[60];
    bcrypt_hashpw(newPassword, bcrypt_gensalt(), hashedPassword);
    char query[100] = "UPDATE users SET password = ? WHERE username = ?";
    executeQuery(query, hashedPassword, username);
}