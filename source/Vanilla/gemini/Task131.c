#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Structure to represent a dynamic array of integers
typedef struct {
    int *data;
    int size;
} IntArray;

// Function to deserialize the string into an IntArray
IntArray deserialize(const char *data) {
    IntArray result = {NULL, 0};
    if (!data || data[0] != '[' || data[strlen(data) - 1] != ']') {
        return result;
    }

    char *inner = strdup(data + 1); // Copy inner part of the string
    inner[strlen(inner) - 1] = '\0'; // Remove the closing bracket

    char *token = strtok(inner, ",");
    while (token) {
        // Trim leading/trailing whitespace from the token
        int i = 0, j = strlen(token) - 1;
        while (isspace(token[i])) i++;
        while (isspace(token[j])) j--;
        token[j + 1] = '\0';

        // Convert the token to an integer
        int value;
        if (sscanf(token + i, "%d", &value) == 1) {
            result.size++;
            result.data = realloc(result.data, result.size * sizeof(int));
            result.data[result.size - 1] = value;
        }

        token = strtok(NULL, ",");
    }
    free(inner);
    return result;
}

int main() {
    IntArray arr1 = deserialize("[1, 2, 3]");
    IntArray arr2 = deserialize("[]");
    IntArray arr3 = deserialize("[1,a,2,3]");
    IntArray arr4 = deserialize(NULL);
    IntArray arr5 = deserialize("1, 2, 3");

    for(int i=0; i < arr1.size; i++) printf("%d ", arr1.data[i]); printf("\n");
    for(int i=0; i < arr2.size; i++) printf("%d ", arr2.data[i]); printf("\n");
    for(int i=0; i < arr3.size; i++) printf("%d ", arr3.data[i]); printf("\n");
    for(int i=0; i < arr4.size; i++) printf("%d ", arr4.data[i]); printf("\n");
    for(int i=0; i < arr5.size; i++) printf("%d ", arr5.data[i]); printf("\n");

    free(arr1.data);
    free(arr2.data);
    free(arr3.data);
    free(arr4.data);
    free(arr5.data);
    return 0;
}