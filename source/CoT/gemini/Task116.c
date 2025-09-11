#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <shadow.h>


// ... (Implementation for changing password securely using appropriate system calls) ...

int main() {
    // Example test cases (replace with actual usernames and passwords)
    char *usernames[] = {"testuser1", "testuser2", "testuser3", "testuser4", "testuser5"};
    char *passwords[] = {"pwd1", "pwd2", "pwd3", "pwd4", "pwd5"};
    int num_users = sizeof(usernames) / sizeof(usernames[0]);


    for (int i = 0; i < num_users; i++) {

        // ... (Call the password change function and handle errors) ...

    }

    return 0;
}