#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Note:  C does not have built-in dynamic array like std::vector in C++. 
// This example uses a fixed-size array for simplicity.  A more robust
// solution would involve dynamic memory allocation and resizing.

#define MAX_DATA 100
#define MAX_LENGTH 100

typedef struct {
    char data[MAX_DATA][MAX_LENGTH];
    int count;
} Task124;


void addData(Task124 *store, const char *data) {
    if (store->count < MAX_DATA) {
        strncpy(store->data[store->count], data, MAX_LENGTH -1); // Prevent buffer overflow
        store->data[store->count][MAX_LENGTH-1] = '\0'; // Null-terminate
        store->count++;
    } else {
        fprintf(stderr, "Error: Data store is full.\n");
    }
}

char* getData(Task124 *store, int index) {
    if (index >= 0 && index < store->count) {
        return store->data[index];
    }
    return NULL;
}



int main() {
    Task124 dataStore = { .count = 0 };


    // Test cases
    addData(&dataStore, "1234-5678-9012-3456");
    addData(&dataStore, "John Doe");
    addData(&dataStore, "9876-5432-1098-7654");
    addData(&dataStore, "Jane Smith");
    addData(&dataStore, "5454-1212-7878-4545");


    printf("%s\n", getData(&dataStore, 0)); // 1234-5678-9012-3456
    printf("%s\n", getData(&dataStore, 1)); // John Doe
    printf("%s\n", getData(&dataStore, 2)); // 9876-5432-1098-7654
    printf("%s\n", getData(&dataStore, 3)); // Jane Smith
    printf("%s\n", getData(&dataStore, 4)); // 5454-1212-7878-4545

    return 0;
}