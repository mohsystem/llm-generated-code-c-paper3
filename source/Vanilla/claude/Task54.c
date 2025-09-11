
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERS 100
#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define OTP_LENGTH 6

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

typedef struct {
    char username[MAX_USERNAME];
    char otp[OTP_LENGTH + 1];
} OTPEntry;

User users[MAX_USERS];
OTPEntry otpMap[MAX_USERS];
int userCount = 0;
int otpCount = 0;

void generateOTP(const char* username, char* otp) {
    srand(time(NULL));
    sprintf(otp, "%06d", rand() % 1000000);
    
    strcpy(otpMap[otpCount].username, username);
    strcpy(otpMap[otpCount].otp, otp);
    otpCount++;
}

int validateOTP(const char* username, const char* otp) {
    for(int i = 0; i < otpCount; i++) {
        if(strcmp(otpMap[i].username, username) == 0) {
            if(strcmp(otpMap[i].otp, otp) == 0) {
                // Remove OTP by shifting array
                for(int j = i; j < otpCount - 1; j++) {
                    strcpy(otpMap[j].username, otpMap[j+1].username);
                    strcpy(otpMap[j].otp, otpMap[j+1].otp);
                }
                otpCount--;
                return 1;
            }
            return 0;
        }
    }
    return 0;
}

int registerUser(const char* username, const char* password) {
    for(int i = 0; i < userCount; i++) {
        if(strcmp(users[i].username, username) == 0) {
            return 0;
        }
    }
    
    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    userCount++;
    return 1;
}

int login(const char* username, const char* password, const char* otp) {
    for(int i = 0; i < userCount; i++) {
        if(strcmp(users[i].username, username) == 0) {
            if(strcmp(users[i].password, password) == 0) {
                return validateOTP(username, otp);
            }
            return 0;
        }
    }
    return 0;
}

int main() {
    char otp[OTP_LENGTH + 1];
    
    // Test case 1: Successful registration and login
    registerUser("user1", "pass123");
    generateOTP("user1", otp);
    printf("Test 1: %d\\n", login("user1", "pass123", otp));
    
    // Test case 2: Wrong password
    registerUser("user2", "pass456");
    generateOTP("user2", otp);
    printf("Test 2: %d\\n", login("user2", "wrongpass", otp));
    
    // Test case 3: Wrong OTP
    registerUser("user3", "pass789");
    generateOTP("user3", otp);
    printf("Test 3: %d\\n", login("user3", "pass789", "000000"));
    
    // Test case 4: Reusing OTP
    registerUser("user4", "pass321");
    generateOTP("user4", otp);
    login("user4", "pass321", otp);
    printf("Test 4: %d\\n", login("user4", "pass321", otp));
    
    // Test case 5: Non-existent user
    generateOTP("user5", otp);
    printf("Test 5: %d\\n", login("user5", "pass999", otp));
    
    return 0;
}
