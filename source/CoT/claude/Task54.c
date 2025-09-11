
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define OTP_LENGTH 6
#define OTP_VALIDITY_SECONDS 300 // 5 minutes

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char otp[OTP_LENGTH + 1];
    time_t timestamp;
} OTPData;

typedef struct {
    User users[MAX_USERS];
    int userCount;
    OTPData otpStore[MAX_USERS];
    int otpCount;
} Task54;

void initTask54(Task54* auth) {
    auth->userCount = 0;
    auth->otpCount = 0;
}

void generateOTP(char* otp) {
    srand(time(NULL));
    for(int i = 0; i < OTP_LENGTH; i++) {
        otp[i] = '0' + (rand() % 10);
    }
    otp[OTP_LENGTH] = '\\0';
}

bool registerUser(Task54* auth, const char* username, const char* password) {
    if(!username || !password || strlen(username) == 0 || strlen(password) == 0) {
        return false;
    }
    
    if(auth->userCount >= MAX_USERS) {
        return false;
    }
    
    // Check if user already exists
    for(int i = 0; i < auth->userCount; i++) {
        if(strcmp(auth->users[i].username, username) == 0) {
            return false;
        }
    }
    
    strncpy(auth->users[auth->userCount].username, username, MAX_USERNAME_LENGTH - 1);
    strncpy(auth->users[auth->userCount].password, password, MAX_PASSWORD_LENGTH - 1);
    auth->userCount++;
    return true;
}

bool validateFirstFactor(Task54* auth, const char* username, const char* password) {
    if(!username || !password) {
        return false;
    }
    
    for(int i = 0; i < auth->userCount; i++) {
        if(strcmp(auth->users[i].username, username) == 0) {
            return strcmp(auth->users[i].password, password) == 0;
        }
    }
    return false;
}

bool generateAndStoreOTP(Task54* auth, const char* username, char* otp) {
    if(!username || auth->otpCount >= MAX_USERS) {
        return false;
    }
    
    // Check if user exists
    bool userExists = false;
    for(int i = 0; i < auth->userCount; i++) {
        if(strcmp(auth->users[i].username, username) == 0) {
            userExists = true;
            break;
        }
    }
    
    if(!userExists) {
        return false;
    }
    
    generateOTP(otp);
    
    // Store OTP
    strncpy(auth->otpStore[auth->otpCount].username, username, MAX_USERNAME_LENGTH - 1);
    strncpy(auth->otpStore[auth->otpCount].otp, otp, OTP_LENGTH);
    auth->otpStore[auth->otpCount].timestamp = time(NULL);
    auth->otpCount++;
    
    return true;
}
//todo    //incomplete code
// bool validateOTP(Task54* auth, const char* username', type='text')