#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#ifdef _WIN32
// Windows-specific code for random number generation would go here
// For this example, we will use the less secure rand() on Windows
// and provide a warning. In production, use Windows Cryptography API.
#include <windows.h>
#pragma comment(lib, "advapi32.lib")
#else
#include <unistd.h>
#include <fcntl.h>
#endif

#define MAX_USERS 10
#define USERNAME_MAX_LEN 64
#define OTP_LEN 6
#define OTP_STR_LEN (OTP_LEN + 1)
#define OTP_VALIDITY_SECS 60

typedef struct {
    char username[USERNAME_MAX_LEN];
    char otp[OTP_STR_LEN];
    time_t timestamp;
} OtpData;

// In-memory store for OTPs. In a real application, use a database or a cache.
static OtpData otp_store[MAX_USERS];
static int otp_store_count = 0;

/**
 * Performs a constant-time comparison of two strings of a given length.
 */
bool constant_time_compare(const char* a, const char* b, size_t len) {
    if (!a || !b) return false;
    unsigned char result = 0;
    for (size_t i = 0; i < len; ++i) {
        result |= a[i] ^ b[i];
    }
    return result == 0;
}

/**
 * Generates a cryptographically secure random number.
 * Note: On Windows, for simplicity, this example falls back to rand().
 * A production implementation should use the Cryptography API (e.g., BCryptGenRandom).
 */
unsigned int get_secure_random_int() {
    unsigned int random_value = 0;
#ifdef _WIN32
    // WARNING: In a production environment on Windows, use BCryptGenRandom.
    // rand() is not cryptographically secure.
    srand((unsigned int)time(NULL));
    random_value = rand();
#else
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd == -1) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    if (read(fd, &random_value, sizeof(random_value)) == -1) {
        perror("Failed to read from /dev/urandom");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
#endif
    return random_value;
}

/**
 * Generates a random OTP for a user.
 * Caller is responsible for freeing the returned string.
 */
char* generate_otp(const char* username) {
    if (!username || strlen(username) == 0 || strlen(username) >= USERNAME_MAX_LEN) {
        return NULL;
    }

    unsigned int otp_val = get_secure_random_int() % 1000000;
    
    char* otp_str = (char*)malloc(OTP_STR_LEN);
    if (!otp_str) {
        return NULL;
    }
    snprintf(otp_str, OTP_STR_LEN, "%06u", otp_val);

    int user_index = -1;
    for (int i = 0; i < otp_store_count; ++i) {
        if (strncmp(otp_store[i].username, username, USERNAME_MAX_LEN) == 0) {
            user_index = i;
            break;
        }
    }
    
    if (user_index == -1 && otp_store_count < MAX_USERS) {
        user_index = otp_store_count++;
    }

    if (user_index != -1) {
        strncpy(otp_store[user_index].username, username, USERNAME_MAX_LEN - 1);
        otp_store[user_index].username[USERNAME_MAX_LEN-1] = '\0';
        strncpy(otp_store[user_index].otp, otp_str, OTP_STR_LEN - 1);
        otp_store[user_index].otp[OTP_STR_LEN-1] = '\0';
        otp_store[user_index].timestamp = time(NULL);
    } else {
        // Store is full, cannot add new user
        free(otp_str);
        return NULL;
    }

    return otp_str;
}

/**
 * Verifies the submitted OTP for a given user.
 */
bool verify_otp(const char* username, const char* submitted_otp) {
    if (!username || !submitted_otp || strlen(submitted_otp) != OTP_LEN) {
        return false;
    }

    int user_index = -1;
    for (int i = 0; i < otp_store_count; ++i) {
        if (strncmp(otp_store[i].username, username, USERNAME_MAX_LEN) == 0) {
            user_index = i;
            break;
        }
    }

    if (user_index == -1) {
        return false;
    }

    OtpData data = otp_store[user_index];
    
    // Invalidate OTP by removing the entry
    // A simple way is to move the last element into this spot
    if (otp_store_count > 1 && user_index != otp_store_count - 1) {
        otp_store[user_index] = otp_store[otp_store_count - 1];
    }
    otp_store_count--;


    // Check expiration
    if (time(NULL) - data.timestamp > OTP_VALIDITY_SECS) {
        return false;
    }
    
    // Constant-time comparison
    return constant_time_compare(data.otp, submitted_otp, OTP_LEN);
}

int main() {
    const char* test_user = "testuser@example.com";

    // Test Case 1: Successful verification
    printf("--- Test Case 1: Successful Verification ---\n");
    char* otp1 = generate_otp(test_user);
    if (otp1) {
        printf("Generated OTP for %s: %s (for testing)\n", test_user, otp1);
        bool is_valid1 = verify_otp(test_user, otp1);
        printf("Verification successful: %s\n\n", is_valid1 ? "true" : "false");
        free(otp1);
    }

    // Test Case 2: Incorrect OTP
    printf("--- Test Case 2: Incorrect OTP ---\n");
    char* otp2 = generate_otp(test_user);
    if (otp2) {
        printf("Generated OTP for %s: %s (for testing)\n", test_user, otp2);
        const char* wrong_otp = "000000";
        bool is_valid2 = verify_otp(test_user, wrong_otp);
        printf("Verification with wrong OTP (%s) successful: %s\n\n", wrong_otp, is_valid2 ? "true" : "false");
        free(otp2);
    }

    // Test Case 3: OTP Reuse
    printf("--- Test Case 3: OTP Reuse ---\n");
    char* otp3 = generate_otp(test_user);
    if (otp3) {
        printf("Generated OTP for %s: %s (for testing)\n", test_user, otp3);
        verify_otp(test_user, otp3); // First, successful use
        printf("Attempting to reuse OTP %s\n", otp3);
        bool is_valid3 = verify_otp(test_user, otp3); // Second, failed use
        printf("Second verification successful: %s\n\n", is_valid3 ? "true" : "false");
        free(otp3);
    }

    // Test Case 4: Expired OTP
    printf("--- Test Case 4: Expired OTP ---\n");
    char* otp4 = generate_otp(test_user);
    if (otp4) {
        printf("Generated OTP for %s: %s (for testing)\n", test_user, otp4);
        printf("Waiting for 2 seconds to simulate expiration (validity is %d)...\n", 1);
        // Modify OTP validity in memory for a quicker test
        for(int i = 0; i < otp_store_count; ++i) {
            if (strncmp(otp_store[i].username, test_user, USERNAME_MAX_LEN) == 0) {
                 otp_store[i].timestamp -= (OTP_VALIDITY_SECS + 1);
            }
        }
        bool is_valid4 = verify_otp(test_user, otp4);
        printf("Verification of expired OTP successful: %s\n\n", is_valid4 ? "true" : "false");
        free(otp4);
    }

    // Test Case 5: No OTP for User
    printf("--- Test Case 5: No OTP Generated for User ---\n");
    bool is_valid5 = verify_otp("nouser@example.com", "123456");
    printf("Verification for non-existent OTP successful: %s\n\n", is_valid5 ? "true" : "false");

    return 0;
}