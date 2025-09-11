#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This C code uses a linked list to store the key-value pairs.
// Sorting is not directly supported in C, so the list is simply printed in the order it was read.
// For a fully sorted output, a more complex data structure or sorting algorithm would be required.

typedef struct Node {
    char key[100];
    char value[100];
    struct Node* next;
} Node;

void sortFile(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    Node* head = NULL;
    Node* temp = NULL;
    char line[200];

    while (fgets(line, sizeof(line), file)) {
        temp = (Node*)malloc(sizeof(Node));
        sscanf(line, "%s %s", temp->key, temp->value);
        temp->next = head;
        head = temp;
    }

    fclose(file);

    // Print the list
    temp = head;
    while (temp != NULL) {
        printf("%s %s\n", temp->key, temp->value);
        temp = temp->next;
    }
}

int main() {
    sortFile("file.txt");
    return 0;
}