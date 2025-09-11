
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define OTP_LENGTH 6
#define OTP_VALIDITY_MINUTES 5
#define MAX_USERS 10
#define MAX_STRING_LENGTH 50

typedef struct {
    char username[MAX_STRING_LENGTH];
    char password[MAX_STRING_LENGTH];
    char otp[OTP_LENGTH + 1];
    time_t otpGenerationTime;
} UserAuth;

typedef struct {
    UserAuth users[MAX_USERS];
    int userCount;
} Task54;

void initializeUsers(Task54* auth) {
    auth->userCount = 2;
    
    strncpy(auth->users[0].username, "user1", MAX_STRING_LENGTH - 1);
    strncpy(auth->users[0].password, "pass1", MAX_STRING_LENGTH - 1);
    auth->users[0].otp[0] = '\\0';
    
    strncpy(auth->users[1].username, "user2", MAX_STRING_LENGTH - 1);
    strncpy(auth->users[1].password, "pass2", MAX_STRING_LENGTH - 1);
    auth->users[1].otp[0]', type='text')