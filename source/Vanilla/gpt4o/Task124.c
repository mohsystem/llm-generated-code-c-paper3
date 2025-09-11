#include <stdio.h>
#include <string.h>

#define MAX_DATA 5
#define MAX_LENGTH 50

typedef struct {
    char sensitiveData[MAX_DATA][MAX_LENGTH];
    int count;
} Task124;

void encrypt(char* data, char* result) {
    int length = strlen(data);
    for (int i = 0; i < length; i++) {
        result[i] = data[length - i - 1];
    }
    result[length] = '\0';
}

void decrypt(char* data, char* result) {
    encrypt(data, result);  // Reversing the encryption reverses the string
}

void storeData(Task124* task, const char* data) {
    if (task->count < MAX_DATA) {
        encrypt((char*)data, task->sensitiveData[task->count]);
        task->count++;
    }
}

char* retrieveData(Task124* task, int index) {
    static char result[MAX_LENGTH];
    if (index >= 0 && index < task->count) {
        decrypt(task->sensitiveData[index], result);
        return result;
    }
    return NULL;
}

int main() {
    Task124 task = {.count = 0};
    storeData(&task, "1234-5678-9012-3456");
    storeData(&task, "Alice Wonderland");
    storeData(&task, "9876-5432-1098-7654");
    storeData(&task, "Bob Builder");
    storeData(&task, "4321-8765-2109-6543");

    printf("%s\n", retrieveData(&task, 0));
    printf("%s\n", retrieveData(&task, 1));
    printf("%s\n", retrieveData(&task, 2));
    printf("%s\n", retrieveData(&task, 3));
    printf("%s\n", retrieveData(&task, 4));

    return 0;
}