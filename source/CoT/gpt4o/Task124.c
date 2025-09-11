#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DATA 5
#define MAX_LENGTH 50

typedef struct {
    char sensitiveData[MAX_DATA][MAX_LENGTH];
    int dataCount;
} Task124;

int isValidData(const char* data) {
    return data != NULL && strlen(data) > 0 && strspn(data, " ") != strlen(data);
}

void encryptData(char* data) {
    size_t len = strlen(data);
    for (size_t i = 0; i < len / 2; ++i) {
        char temp = data[i];
        data[i] = data[len - i - 1];
        data[len - i - 1] = temp;
    }
}

void decryptData(char* data) {
    encryptData(data);  // Reversing again decrypts it
}

void addData(Task124* storage, const char* data) {
    if (isValidData(data) && storage->dataCount < MAX_DATA) {
        strncpy(storage->sensitiveData[storage->dataCount], data, MAX_LENGTH - 1);
        storage->sensitiveData[storage->dataCount][MAX_LENGTH - 1] = '\0';
        encryptData(storage->sensitiveData[storage->dataCount]);
        storage->dataCount++;
    }
}

const char* getData(Task124* storage, int index) {
    if (index >= 0 && index < storage->dataCount) {
        static char data[MAX_LENGTH];
        strncpy(data, storage->sensitiveData[index], MAX_LENGTH);
        decryptData(data);
        return data;
    }
    return NULL;
}

int main() {
    Task124 storage = { .dataCount = 0 };
    addData(&storage, "1234-5678-9012-3456");
    addData(&storage, "John Doe");
    addData(&storage, "9876-5432-1098-7654");
    addData(&storage, "Jane Smith");
    addData(&storage, "2345-6789-0123-4567");

    for (int i = 0; i < 5; ++i) {
        const char* data = getData(&storage, i);
        if (data != NULL) {
            printf("%s\n", data);
        }
    }

    return 0;
}