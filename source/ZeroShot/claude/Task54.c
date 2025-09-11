
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_USERS 100
#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50
#define OTP_LENGTH 7

typedef struct {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

typedef struct {
    char username[USERNAME_LENGTH];
    char otp[OTP_LENGTH];
} OTPEntry;

User users[MAX_USERS];
OTPEntry otpStore[MAX_USERS];
int userCount = 0;
int otpCount = 0;

void generateOTP(char* otp) {
    srand(time(NULL));
    for(int i = 0; i < 6; i++) {
        otp[i] = '0' + (rand() % 10);
    }
    otp[6] = '\\0';
}

bool registerUser(const char* username, const char* password) {
    if(userCount >= MAX_USERS) return false;
    
    for(int i = 0; i < userCount; i++) {
        if(strcmp(users[i].username, username) == 0) {
            return false;
        }
    }
    
    strncpy(users[userCount].username, username, USERNAME_LENGTH-1);
    strncpy(users[userCount].password, password, PASSWORD_LENGTH-1);
    userCount++;
    return true;
}

char* sendOTP(const char* username) {
    if(otpCount >= MAX_USERS) return NULL;
    
    for(int i = 0; i < userCount; i++) {
        if(strcmp(users[i].username, username) == 0) {
            strncpy(otpStore[otpCount].username, username, USERNAME_LENGTH-1);
            generateOTP(otpStore[otpCount].otp);
            otpCount++;
            return otpStore[otpCount-1].otp;
        }
    }
    return NULL;
}

bool login(const char* username, const char* password, const char* otp) {
    bool userFound = false;
    for(int i = 0; i < userCount; i++) {
        if(strcmp(users[i].username, username) == 0 && 
           strcmp(users[i].password, password) == 0) {
            userFound = true;
            break;
        }
    }
    
    if(!userFound) return false;
    
    for(int i = 0; i < otpCount; i++) {
        if(strcmp(otpStore[i].username, username) == 0 && 
           strcmp(otpStore[i].otp, otp) == 0) {
            // Remove OTP by shifting array
            for(int j = i; j < otpCount-1; j++) {
                strcpy(otpStore[j].username, otpStore[j+1].username);
                strcpy(otpStore[j].otp, otpStore[j+1].otp);
            }
            otpCount--;
            return true;
        }
    }
    return false;
}

int main() {
    // Test Case 1: Successful registration
    printf("Test 1: %d\\n", registerUser("user1", "pass123"));
    
    // Test Case 2: Registration with existing username
    printf("Test 2: %d\\n", registerUser("user1", "pass456"));
    
    // Test Case 3: Generate and verify OTP
    char* otp = sendOTP("user1");
    printf("Test 3: %d\\n", login("user1", "pass123", otp));
    
    // Test Case 4: Login with wrong OTP
    printf("Test 4: %d\\n", login("user1", "pass123", "000000"));
    
    // Test Case 5: Login with expired/used OTP
    printf("Test 5: %d\\n", login("user1", "pass123", otp));
    
    return 0;
}
