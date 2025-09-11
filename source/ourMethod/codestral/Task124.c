#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LENGTH 100
#define MAX_DATA_LENGTH 100

typedef struct {
    char key[MAX_KEY_LENGTH];
    char data[MAX_DATA_LENGTH];
} SensitiveData;

SensitiveData* sensitiveData = NULL;
int dataCount = 0;

void storeData(const char* key, const char* data) {
    if (key != NULL && data != NULL) {
        // Encrypt the data before storing it
        char* encryptedData = encrypt(data);

        sensitiveData = (SensitiveData*)realloc(sensitiveData, (dataCount + 1) * sizeof(SensitiveData));
        strcpy(sensitiveData[dataCount].key, key);
        strcpy(sensitiveData[dataCount].data, encryptedData);
        dataCount++;

        free(encryptedData);
    } else {
        printf("Key and data cannot be NULL\n");
    }
}

char* retrieveData(const char* key) {
    if (key != NULL) {
        for (int i = 0; i < dataCount; i++) {
            if (strcmp(sensitiveData[i].key, key) == 0) {
                // Decrypt the data before returning it
                char* decryptedData = decrypt(sensitiveData[i].data);
                return decryptedData;
            }
        }
        printf("Data not found for the given key\n");
        return NULL;
    } else {
        printf("Key cannot be NULL\n");
        return NULL;
    }
}

char* encrypt(const char* data) {
    // Placeholder for encryption logic
    char* encryptedData = (char*)malloc((strlen(data) + 1) * sizeof(char));
    strcpy(encryptedData, data);
    return encryptedData;
}

char* decrypt(const char* data) {
    // Placeholder for decryption logic
    char* decryptedData = (char*)malloc((strlen(data) + 1) * sizeof(char));
    strcpy(decryptedData, data);
    return decryptedData;
}

int main() {
    // Test case 1: Storing sensitive data
    char key1[MAX_KEY_LENGTH], data1[MAX_DATA_LENGTH];
    printf("Enter key for test case 1: ");
    fgets(key1, MAX_KEY_LENGTH, stdin);
    key1[strcspn(key1, "\n")] = '\0'; // Remove trailing newline
    printf("Enter data for test case 1: ");
    fgets(data1, MAX_DATA_LENGTH, stdin);
    data1[strcspn(data1, "\n")] = '\0'; // Remove trailing newline
    storeData(key1, data1);
    printf("Data stored successfully for test case 1\n");

    // Test case 2: Retrieving sensitive data
    char key2[MAX_KEY_LENGTH];
    printf("Enter key for test case 2: ");
    fgets(key2, MAX_KEY_LENGTH, stdin);
    key2[strcspn(key2, "\n")] = '\0'; // Remove trailing newline
    char* retrievedData = retrieveData(key2);
    if (retrievedData != NULL) {
        printf("Retrieved data for test case 2: %s\n", retrievedData);
        free(retrievedData);
    }

    // Test case 3: Storing NULL key
    storeData(NULL, "test data");

    // Test case 4: Storing NULL data
    storeData("test key", NULL);

    // Test case 5: Retrieving data with NULL key
    retrieveData(NULL);

    free(sensitiveData);
    return 0;
}