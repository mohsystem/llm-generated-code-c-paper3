#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h> // For usleep


// Define a simple structure for a user
typedef struct User {
    char username[50];
    char password[50];
} User;

// Sample user database (insecure in real-world scenarios)
User users[] = {
    {"user1", "password123"},
    {"user2", "securepass"},
    {"user3", "anotherpassword"},
};
int num_users = sizeof(users) / sizeof(users[0]);

// Constant-time comparison function to prevent timing attacks
bool constant_time_compare(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
      return false; // Handle NULL inputs
    }
    
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    if (len1 != len2) {
        return false;
    }

    bool match = true;
    for (size_t i = 0; i < len1; i++) {
        if (s1[i] != s2[i]) {
            match = false;
        }
    }
    // Introduce a delay to minimize timing information leaks
    usleep(10000); // Sleep for 10 milliseconds
    return match;

}


bool authenticate(const char *username, const char *password) {
    if (username == NULL || password == NULL) {
      return false; // Handle NULL inputs
    }

    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0 && constant_time_compare(password, users[i].password)) {
            return true;
        }
    }
    return false;
}

int main() {
    printf("%d\n", authenticate("user1", "password123")); // true
    printf("%d\n", authenticate("user2", "wrongpass")); // false
    printf("%d\n", authenticate("user3", "anotherpassword")); // true
    printf("%d\n", authenticate("nonexistentuser", "password")); // false
    printf("%d\n", authenticate(NULL, "password")); // false
    return 0;
}